# GDNative demo

Does nothing useful but to demonstrate the use of a GDNative script.

**Note:** this has been tested with Godot 3.1 and uses nativescript-1.1

Further information can be found at https://docs.godotengine.org/en/3.1/tutorials/plugins/gdnative/gdnative-cpp-example.html

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
(path/to/godot --gdnative-generate-json-api godot_api.json   <--- build up-to-date bindings. ONLY NEEDED if you know what you are doing)
scons -j8 p={windows|x11} headers=godot_headers generate_bindings=yes bits=64
```

Note that you may want to update godot-cpp to the current master, especially when using a more recent
Godot version than 3.1.

## Building

After having prepared everything, type into a Visual Studio Native Tools prompt:

```
scons p={windows|x11}
```

This should create `bin\win64\libgdexample.dll`

### Visual Studio project generation
If you're using Visual Studio under windows, you can create a `.sln` solution file using

```
scons p=windows project.sln
```

When you open this file in Visual Studio, everything should work. Note, however, that the
IntelliSense completion and error display will likely not work. While you can "Build -> Build
solution", the error list in case of errors will contain a lot of spam. To resolve this,
click on the "Build + IntelliSense" box on the "Error List" bottom pane, and select "Build only"
instead to only see errors from the actual compiling phase.

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
MyClass::_init()
```
