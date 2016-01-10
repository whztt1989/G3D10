G3D 10.xx Build System Instructions
===========================================

G3D builds with a Python script named "buildg3d". All of the software
required for building and using G3D is available for free on all
platforms. 

Downloading and building G3D takes about 30 minutes on a recent
desktop computer with a fast network connection. The source code
repository contains all of the library dependencies. Once you've built
G3D, you can update to a newer release in a few minutes as an
incremental build.

Binary releases of G3D are available, however we recommend building
G3D yourself from source so that you can step into it when debugging
and access the latest changes from subversion.


Windows
------------
### Install:

1. 64-bit Windows 7, 8.1, or 10
2. [Python 3.4 or later](https://www.python.org/downloads/windows/)
3. Visual Studio 2015 or later, either the Professional 
   or the [free Community version](https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx)
4. A subversion client such as [TortoiseSVN](http://tortoisesvn.net/downloads.html)

### Asset Packs (Optional):

G3D includes common asset files for making games, demos, and research
projects, as well as for its own sample programs and automated tests.
The asset packs are large, so they are an optional download.

To install *all* of the asset packs, SVN check out 
`https://g3d.svn.codeplex.com/svn/data10` to `%g3d%/data10`.
Or, if you prefer, check out only the [subdirectories of
data10](https://g3d.codeplex.com/SourceControl/latest#data10/readme.md)
that you need into `%g3d%/data10/`.


### Configure & Build:

1. Create a directory for G3D, such as `c:\g3d`, and set a `%g3d%` **system** environment variable to its path. 
   - This is not required, but the instructions below are relative to this variable
2. SVN check out `https://g3d.svn.codeplex.com/svn/G3D10` to `%g3d%/G3D10`
3. Set the **user** environment variable `G3D10DATA=%g3d%/build/data`
4. Set the system-wide VC Directories in `Microsoft.Cpp.Win64.user.props` explicitly, or through the Visual Studio IDE (View->Other Windows->Property Manager, G3D->starter->Release|x64->Microsoft.Cpp.x64.user->properties->VC++ Directories):
   - Include: `%g3d%/build/include`
   - Library: `%g3d%/build/lib`
5. Add `%g3d/build/bin` to your `PATH` environment variable (so that Windows can find DLLs when launching your own programs)
6. At a command prompt in the `%g3d%/G3D10` directory, run `buildg3d lib data`

We recommend copying the contents of
`%g3d%/build/samples/starter` to your own directory when
creating your own new G3D projects. It includes a typical directory
structure and Visual Studio project files.

See also the Visual Studio integration files in the G3D10/bin
directory and the Visual Studio installation notes in the
documentation.

_It is possible to build the library on Windows using the Visual Studio
IDE, however documentation, headers, demos, and other aspects of the
full build will be missing. Dependencies are sometimes processed
incorrectly if you haven't run the full command-line build first. The
G3D team **DOES NOT SUPPORT** direct use of the Visual Studio project
files.  We only support the buildg3d script that calls them._

### Advanced (Optional):

The G3D development team uses the header files and data files directly
from the source tree. We're continuously changing these and want to
ensure that we're stepping into and modifying the latest version. If
you wish to do this as well, then make the following changes.

Remove `%g3d%/build/include` from your VC include
directory. In its stead, add:

    %g3d%/G3D10/assimp.lib/include
    %g3d%/G3D10/civetweb.lib/include
    %g3d%/G3D10/enet.lib/include
    %g3d%/G3D10/freeimage.lib/include
    %g3d%/G3D10/glew.lib/include
    %g3d%/G3D10/glfw.lib/include
    %g3d%/G3D10/nfd.lib/include
    %g3d%/G3D10/qrencode.lib/include
    %g3d%/G3D10/zip.lib/include
    %g3d%/G3D10/zlib.lib/include
    %g3d%/G3D10/G3D.lib/include
    %g3d%/G3D10/GLG3D.lib/include
    %g3d%/G3D10/GLG3DVR.lib/include
    %g3d%/G3D10/LibOVR.lib/include
    %g3d%/G3D10/LibOVRKernel.lib/include

Set your `G3D10DATA` environment variable to include a
semicolon-separated list of your asset pack locations. If you use all
asset packs, this is:

    %g3d%/G3D10/data-files;%g3d%/data10/common;%g3d%/data10/research;%g3d%/data10/game

You can create your own private asset packs and add them to this
variable, of course.

The development team uses the [Markdown
Preview](https://chrome.google.com/webstore/detail/markdown-preview/jmchmkecamhbiokiopfpnfgbidieafmd?hl=en)
Chrome extension to view documents like this readme.md file directly
in a web browser.

OS X
-------------
Because OS X video drivers are produced by Apple as part of the operating system, they tend to lag the features
on Windows by about a year. The G3D build on OS X uses legacy support to emulate these features for you. If you
have a choice, we recommend developing on Windows.

Install:

1. OS X 10.10.4 or later
2. [Python 3.4 or later](https://www.python.org/downloads/mac-osx/)
3. LLVM 3.6.0 and clang, from [Xcode](https://developer.apple.com/xcode/)
4. [yasm 1.3](http://www.macports.org/ports.php?by=name&substr=yasm) via macports
5. [Exuberant-ctags](http://www.macports.org/ports.php?by=library&substr=ctags) via macports

Follow the Windows instructions above, setting your `g3d`,
`G3D10DATA`, `INCLUDE`, `LIBRARY`, and `PATH` environment variables
accordingly. Note that OS X paths are delimited by colons instead of
semicolons.

The OSX and Linux builds will install an internal version of FFMPEG
(http://ffmpeg.org/) to the G3D installation directory, so be careful
not to overwrite a previously installed version unintentionally.

Linux
--------------

The G3D Linux build is experimental and unsupported. We perform
primary development on Windows and port monthly to OS X. The Linux
build is updated about twice a year.

Install:

1. Ubuntu Linux 14
2. Python 3.4
3. LLVM and clang, or gcc/g++
4. The following library packages: All of these packages can be installed on Ubuntu with bin/ubuntu_config.sh
 1. Current version of [libzip](http://nih.at/libzip/)
 2. Current version of [libz](http://www.zlib.net/)
 3. Current version of mesa
 4. Current version of xrandr
 5. Current version of xi
 6. Current version of libxxf86vm
 7. Current version of libxcursor
 8. Current version of libgtk
 9. Current version of libncurses
 10. Exuberant-ctags


Follow the Windows instructions above, setting your `g3d`,
`G3D10DATA`, `INCLUDE`, `LIBRARY`, and `PATH` environment variables
accordingly. Note that Linux paths are delimited by colons instead of
semicolons.

The OSX and Linux builds will install an internal version of FFMPEG
(http://ffmpeg.org/) to the G3D installation directory, so be careful
not to overwrite a previously installed version unintentionally.



Documentation (Optional)
--------------------------

The G3D documentation for the latest release and subversion top of
tree are available online. If you wish to build a local copy of the
documentation, you'll need the following:

1. [Doxygen 1.8.0 or later](http://www.doxygen.org)
  - on Windows, add the install directory to your `PATH` variable
  - on OS X, add `/Applications/Doxygen.app/Contents/Resources/` to your `PATH` variable
2. LaTeX
  - use [MikTex](http://miktex.org/) for Windows
  - for all other platforms, use [TexLive](https://www.tug.org/texlive)
3. [Ghostscript](http://pages.cs.wisc.edu/~ghost/)



--------------------------------------------------------------------
Run "buildg3d help" for more information about the build sytem.

Post on g3d-users@googlegroups.com with questions about the build system.

