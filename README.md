### cbcp & cbps

cbcp -> Copy stdin to the X11 clipboard

cbps -> Paste X11 clipboard to stdout

## Usage
```bash
echo Some command with output text | cbcp
cbps | [Some command]
cbcp < or_copy_content_of_file_to_clipboard.txt
cbps > paste_content_of_clipboard_to_file.txt
```

## Build and Install
Option 1 : On Debian based distributions (debian, ubuntu, mint, ...)
```bash
make
sudo apt install $(ls ./cbcp*.deb)
```

Option 2 : Build and install executables in ${HOME}/bin
```bash
make
make install
```

Program is copied to ~/bin -> make sure it is in your PATH

## Cleanup

```bash
make clean
make uninstall
```