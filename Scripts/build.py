#!/usr/bin/env python3
from ue4helpers import ProjectPackager, VersionHelpers
from os.path import abspath, dirname

# Create our project packager
packager = ProjectPackager(
    # The root directory for the project
    # (This example assumes this script is in a subdirectory)
    root=dirname(dirname(abspath(__file__))),
    # Use the date of the most recent git commit as our version string
    version=VersionHelpers.from_git_commit(),
    # The filename template for our generated .zip file
    archive="{name}-Nightly-{version}-{platform}",
    # Don't strip debug symbols from the packaged build
    strip_debug=False,
    # Don't strip manifest files from the packaged build
    strip_manifests=False,
)

# Clean any previous build artifacts
packager.clean()

# Package the project
packager.package()

# Compress the packaged distribution
# (The CI system can then tag the generated .zip file as a build artifact)
packager.archive()
