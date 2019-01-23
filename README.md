# GDNative demo

Does nothing useful but to demonstrate the use of a GDNative script.

**Note:** this has been tested with Godot 3.0.3.
It uses the old Nativescript 1.0; better use 1.1 in the future.

Further information can be found at https://docs.godotengine.org/en/3.0/tutorials/plugins/gdnative/gdnative-cpp-example.html

## Directory structure

```
./
|-- bin                            Output directory for the binary plugin
|   |-- x11                        which has its sources in native/
|   `-- win64
|
`-- native                         C++ source files for the binary plugin
    |-- godot-cpp                  Godot C++ bindings
    `-- src                        The actual source code
```

## Installation

### Dependencies

Install the **scons** build system.

### Preparation

Run `git submodule update --init --recursive` to initialize the submodules.

Then open the shell / the Visual Studio Native Tools prompt, and do:

```
cd godot-cpp
scons -c      <--- cleans up any previous build
(path/to/godot --gdnative-generate-json-api godot_api.json   <--- build up-to-date bindings. ONLY NEEDED for godot != 3.0)
scons -j8 p={windows|x11} headers=godot_headers generate_bindings=yes
```

Note that you may want to update godot-cpp to the current master, especially when using a more recent
Godot version than 3.0. Note that when *not* using the `nativescript-1.0` branch, the code will not
compile any more, requiring small changes. These are documented in the latest godot docs.

## Building

After having prepared everything, type into a Visual Studio Native Tools prompt:

```
scons p={windows|x11}
```

This should create `bin\win64\libgdexample.lib`

## Running

If the build has succeeded, the project can be opened in godot. Either run
`path/to/godot -e`, while being in the repo's main directory, or open the
project from godot's GUI.

The following output should appear in the Godot console log window (not neccessarily
the "Log" tab inside godot, but the proper terminal window).

```
C:\Users\flo\demo> \path\to\godot\bin\godot.windows.tools.64.exe -e
OpenGL ES 3.0 Renderer: GeForce GTX 1080 Ti/PCIe/SSE2
Construct gdnative interface
MyClass ctor    <-- yayy :)
```
