# Stonks
ICT290 Group Project Part 1

## Building
* Clone the repo:
```
git clone https://github.com/MajorArkwolf/ICT290P1.git
```

* Install dependencies:
    * Linux: `sudo apt-get install cmake freeglut3-dev libsdl1.2-dev`
    * macOS: `brew install cmake sdl`
    * Windows: `.\vcpkg install freeglut sdl1`

* Configure the build:
    * Unix:
    ```
    mkdir build
    cd build
    CXX=clang++ cmake ..
    ```
    * Windows:
        * In Visual Studio, select Open → CMake, select `CMakeLists.txt`

* Build:
    * Unix:
    ```
    make && ./steel-ball-run
    ```
    * Windows:
        * Select Build in Visual Studio

## Contributing
* Ensure your editor uses Unix line endings and leaves an empty new line at
    the end of a file
    * Use [this plugin](https://marketplace.visualstudio.com/items?itemName=JakubBielawa.LineEndingsUnifier)
      for Visual Studio
        * Set `Add newlines on the last line` to `true`
        * Set `Default line ending` to `Linux`
        * Set `Save files after unifying` to `true`
* Use clang-format to style your source code
    * Install a clang-format extension to your editor of choice
        * [vim](https://github.com/rhysd/vim-clang-format)
        * [Atom](https://atom.io/packages/clang-format)
        * [Visual Studio 2017](https://marketplace.visualstudio.com/items?itemName=mynkow.FormatdocumentonSave)
            * VS17 includes support for clang-format, but won't format
                unless you do it manually, so use this extension
        * [Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=xaver.clang-format)
    * Make sure to configure the extension to automatically apply formatting on
        save
