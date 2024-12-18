最近被win11 24H2的蓝屏背刺了，刷了个win10玩玩，但我发现win10的shift + ctrl + s截图工具截图的图片是保存在剪切板中的，不是直接放到C:\Users\%user%\pictures\screenshots\这个目录下的，很麻烦，所以我搞了这么个小玩意儿，**主要作用是读取win10系统剪切板中的dib图片，生成bmp图片再转化为png放到你所指定的目录下，就是模拟了win11的功能**。  
注意：**在使用这个小工具之前确保自己安装了python3.12和opencv-python库，并把python放到环境变量**  
这个项目最后依赖python脚本将bmp文件转化为png，python脚本的源码已经放在仓库中，同时我也提供了编译好的.pyd文件，**如果你想对python文件进行修改，需要运行仓库中的setup.py文件再次编译，所需要的python库有cython和buildTools**  
在运行脚本之前，**请将savePath.ini文件中的savePath的值换成你自己的目录**
