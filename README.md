# genmk
### Quickly generate makefiles  for bioinformatics pipeline analysis or other data analysis projects



## Contents

- [Installation](#Installation)
- [Input format](#Input-format)
- [Quick start](#Quick-start)
- [Usage](#Usage)

## Installation
genmk is built on C++11.

#### install genmk from github (latest version):
```bash
# download and install genmk from github
git clone https://github.com/lixingqiancs/genmk.git
cd genmk
make install
./bin/genmk

# Or add Linux Path
export PATH=$PWD/bin:$PATH 
genmk
```



## Input format

#### Input file (xqmk) format explanation
##### Multiple samples
---
```bash
@sample1
1       0       echo "Sample1 test1"
2       1       echo "Sample1 test2"
3       1,2     echo "Sample1 test3"
@sample2
1       0       echo "Sample2 test1"
2       1       echo "Sample2 test2"
3       1,2     echo "Sample2 test3"
4       all     echo "All"
```
##### Single sample
```bash
1       0       echo "test1"
2       1       echo "test2"
3       1,2     echo "test3"
```
The xqmk file It is composed of three parts:
-	Sample name: Optional, when you have multiple samples to analyze, you need to specify the sample name, ***starting with @***
-	Target information: Required, it must consist of three parts, each of which cannot be missing, ***and the delimiter is "\t"***.
  -	Target Name: It can be written as a number or as a word, when target name is shorter, it will be prefixed with "Job_".
  -	Prerequisites: It is a combination of numbers, each number means the line number of the prerequisite target, separated by commas.
  -	Command: Executable linux command for specific targets, please note that this command must be executable.
-	Final Target: Optional, if you want to perform some summary-like calculations at the end of the pipeline, you can define it in the Final Target, please note that it can only be defined once. Its format is the same as Target information, but the ***Prerequisites column can only write all***.



## Quick start

```bash
# Demo
## You can directly specify the xqmk file, e.g.
genmk -f test.xqmk

## Or by using pipes with your other command, e.g.
cat test.xqmk | genmk -p

## When you do not specify the name of the exported makefile, it will be exported as "makefile" by default. You can use the -o option to specify the name of the exported makefile, e.g.
genmk -f test.xqmk -o test.mk

# Now try to run this makefile pipeline you created
make -f test.mk
```



## Usage

Users can use `genmk` for help.

```bash
Usage: 
        bin/genmk < -f file> or < -p within | (pipeline)> < -o output_file>

Options:
        -f: STR Path of xqmk file
        -p      create makefile from pipeline(|)
        -o: STR Path of output make file
```



License
=======

Copyright (C) 2022 [Xingqian Li](mailto:lixingqiancs@gmail.com)

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later vers
ion.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>.

[Xingqian Li](mailto:lixingqiancs@gmail.com), Department of Chemical Pathology, The Chinese University of Hong Kong, Hong Kong
