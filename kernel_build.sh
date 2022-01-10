#!/bin/bash

make clean -j 4
make bzImage -j 4
make modules -j 4
make -j 4
make install -j 4
make modules_install -j 4
