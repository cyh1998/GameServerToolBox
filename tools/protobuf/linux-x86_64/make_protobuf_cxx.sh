#!/bin/bash
OutputDir="./"

#将当前目录.proto文件编码输出到指定目录
for file in *.proto
do
    sh -xc "./protoc -I ./ --cpp_out=$OutputDir $file"
done
