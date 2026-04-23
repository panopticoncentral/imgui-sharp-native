<#
.SYNOPSIS
    Download and extract the SDL3 Windows VC development package.

.DESCRIPTION
    Used by CI (and optionally local builds) to acquire the SDL3 headers
    and import libraries needed to build libimgui_sharp.dll. Verifies
    SHA256 against scripts/sdl3-versions.json.

.PARAMETER DestDir
    Destination directory. Defaults to "$PSScriptRoot/../sdl3".

.OUTPUTS
    Writes SDL3_ROOT=<path> to $env:GITHUB_ENV when running in GitHub Actions,
    and prints the path to stdout.
#>
[CmdletBinding()]
param(
    [string] $DestDir = (Join-Path $PSScriptRoot '..' 'sdl3')
)

$ErrorActionPreference = 'Stop'

$versionsPath = Join-Path $PSScriptRoot 'sdl3-versions.json'
$versions = Get-Content $versionsPath -Raw | ConvertFrom-Json
$url = $versions.windows.url
$expectedHash = $versions.windows.sha256.ToUpperInvariant()
$sdl3Version = $versions.sdl3_version

New-Item -ItemType Directory -Force -Path $DestDir | Out-Null
$zipPath = Join-Path $DestDir "SDL3-devel-$sdl3Version-VC.zip"
$extractDir = Join-Path $DestDir "SDL3-$sdl3Version"

if (-not (Test-Path $zipPath)) {
    Write-Host "Downloading $url"
    Invoke-WebRequest -Uri $url -OutFile $zipPath -UseBasicParsing
}

$actualHash = (Get-FileHash -Algorithm SHA256 -Path $zipPath).Hash.ToUpperInvariant()
if ($actualHash -ne $expectedHash) {
    throw "SHA256 mismatch for SDL3 zip. Expected $expectedHash, got $actualHash"
}
Write-Host "SHA256 OK: $actualHash"

if (-not (Test-Path $extractDir)) {
    Write-Host "Extracting to $DestDir"
    Expand-Archive -Path $zipPath -DestinationPath $DestDir -Force
}

# The VC zip extracts to SDL3-<version>/ with cmake/ include/ lib/ subdirs.
# find_package(SDL3 CONFIG) looks for SDL3Config.cmake under cmake/.
$sdl3Root = (Resolve-Path $extractDir).Path
Write-Host "SDL3_ROOT=$sdl3Root"

if ($env:GITHUB_ENV) {
    Add-Content -Path $env:GITHUB_ENV -Value "SDL3_ROOT=$sdl3Root"
}

$sdl3Root
