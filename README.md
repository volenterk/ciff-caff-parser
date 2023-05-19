# ciff-caff-parser

## Before using the code:
Requirements:
- `libwebp-dev`

Run:
```
make all
```

To clean the project folder:
```
make clean
```

## Usage: `./parser [OPTIONS] [FILE]`

### Options:
- `-caff [path-to-caff].caff`: Parse the specified .caff file
- `-ciff [path-to-ciff].ciff`: Parse the specified .ciff file

### Description:
The `./parser` program is used to parse CIFF or CAFF files into webp format. The description of the CIFF and CAFF formats can be found here:

- https://www.crysys.hu/downloads/vihima06/2020/CIFF.txt
- https://www.crysys.hu/downloads/vihima06/2020/CAFF.txt

### Examples:
- `./parser -caff examples/caff/1.caff`: Parses the file.caff file.
- `./parser -ciff examples/ciff/example.ciff`: Parses the file.ciff file.
