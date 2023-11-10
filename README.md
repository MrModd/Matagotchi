[![FAP Build](https://github.com/MrModd/Matagotchi/actions/workflows/build.yml/badge.svg)](https://github.com/MrModd/Matagotchi/actions/workflows/build.yml)

# Matagotchi
Tamagotchi like game for Flipper Zero

# Disclamer
This application is still under initial development

# Build
Build with [ufbt](https://github.com/flipperdevices/flipperzero-ufbt/tree/dev) passing the `src` folder to the UFBT_APP_DIR like so:

```sh
ufbt UFBT_APP_DIR=$(pwd)/src
```

# Running unit tests
```sh
make test
build/test
```

## Optional: clangd LSP
Create a `compile_commands.json` file with [bear](https://github.com/rizsotto/Bear):

```sh
bear make test
```

# TODO

* Add ability to delete the state in settings
* Add about page in settings
* Add hp feature
* Add animations for stage up
