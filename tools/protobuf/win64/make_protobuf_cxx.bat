set OutputDir = "./"

::将当前目录.proto文件编码输出到指定目录
for %%i in (*.proto) do (
    "protoc.exe" -I ./ --cpp_out %OutputDir% %%i
)

pause