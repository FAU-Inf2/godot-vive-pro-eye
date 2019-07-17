# Godot driver for the HTC Vive Pro Eye equipment

This project provides a Godot driver for the HTC Vive Pro Eye. It uses the
[SRanipal framework](https://developer.vive.com/resources/knowledgebase/vive-sranipal-sdk/).


## Directory structure

```
./
|-- bin                            Output directory for the binary plugin
|   |-- x11                        which has its sources in native/
|   `-- win64
|
`-- native                         C++ source files for the binary plugin
    |-- godot-cpp                  Godot C++ bindings
    |-- SRanipal_SDK               Placeholder directory for the SRanipal files
    `-- src                        The actual source code
```

## Installation

### Dependencies

Install the **scons** build system.

Install the **boost** libraries to `C:\local\boost_1_69_0`. If you choosea
different directory, adjust the `windows_boost_path` variable in `SConstruct`
first.

Download and extract the
[SRanipal SDK](https://developer.vive.com/resources/knowledgebase/vive-sranipal-sdk/)'s
`bin\`, `lib\` and `include\` directories to `native\SRanipal_SDK`. For details, refer
to [the README in that directory](native/SRanipal_SDK/README.txt).

### Preparation

Run `git submodule update --init --recursive` to initialize the submodules.

Then open the shell / the Visual Studio Native Tools prompt, and do:

```
cd godot-cpp
scons -c      <--- cleans up any previous build
(path/to/godot --gdnative-generate-json-api godot_api.json   <--- build up-to-date bindings. ONLY NEEDED if you know what you are doing)
scons -j8 p=windows headers=godot_headers generate_bindings=yes bits=64
```

### Building

After having prepared everything, type into a Visual Studio Native Tools prompt:

```
scons p=windows
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

You may need to install the SRanipal runtime, which is available from the SDK download
page. You may need to perform a calibration first.

The demo application shows a scene with some objects, and three colored spheres.
These spheres follow your gaze and correspond to your right, left, and combined gaze.
If you close one of the eyes, the corresponding sphere's size gets gradually smaller.

# Documentation

Sorry, currrently you can only read the comments in the [header file](native/src/myclass.h).

For use in Godot, the method names are the same. Just create a _Node_-object and attach
the _MyClass.gdns_ script to it. Then you can call `ThatObject.update_eye_data()` and
`ThatObject.get_gaze_direction(0)` from your own GDscripts.

# License

The code offered in this repository is licensed under the MIT license. Note, however,
that by linking in the SRanipal SDK, you have to agree to their license agreement,
which may have an impact on the conditions you are allowed to redistribute the resulting
binaries under.

The license header that's part of every source file is reproduced below:

Copyright (c) 2019 Lehrstuhl für Informatik 2,
Friedrich-Alexander-Universität Erlangen-Nürnberg (FAU)
Author: Florian Jung (florian.jung@fau.de)

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
