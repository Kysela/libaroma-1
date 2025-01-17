#!/bin/sh
cd ../obj

echo Compiling hbucdn
$LIBAROMA_GCC -c \
  -save-temps \
  -fdata-sections -ffunction-sections -Wl,--gc-sections \
  -D_GLIBCXX_DEBUG_PEDANTIC -D_GLIBCXX_DEBUG \
  -fPIC -DPIC -Wl,-s \
 \
  ../../../libs/harfbuzz-ng/src/hb-ucdn/ucdn.c \
 \
  -I../../../libs/harfbuzz-ng/src/hb-ucdn

cd ../libs
