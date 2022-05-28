# Comsol External Functions
Explanation how to use "External" comsol node with Dynamic Link Libraries (DLL's) written on C from scratch.

This guide written 27.05.2022 for 5.5 version of Comsol.\
I found [official version](https://doc.comsol.com/5.5/doc/com.comsol.help.comsol/comsol_ref_definitions.12.047.html) of doc's with External node very poor exlaining how to make it work.

# What do you need to create you own DLL written on C?
1. C program
2. Compiler

Let's install compiler first.\
Website mingw.org does not work anymore, but we can download installer [here](https://sourceforge.net/projects/mingw/).\
Also I keep a copy of installer at the repository [mingw-get-setup.exe]().

1. Launch installer.\
![Launch installer](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_1.png)

2. Set path or keep as it is.\
![Set path or keep as it is.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_2.png)

3. Wait for manager installed.\
![Wait for manager installed.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_3.png)

4. Wait for manager installed.\
![Wait for manager installed.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_4.png)

5. Wait for manager installed.\
![Wait for manager installed.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_5.png)

6. Wait for manager installed.\
![Wait for manager installed.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_6.png)

7. Wait for manager installed.\
![Wait for manager installed.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_7.png)

8. Wait for manager installed.\
![Wait for manager installed.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_8.png)

set environment variables
cmd prompt
```shell script
set PATH=C:\mingw;C:\mingw\bin;%PATH%
```
check if environment variables setted
```shell script
echo %PATH%
```

---

<details>
<summary style="font-size:14px">View code</summary>
<p>

\```md
  code

\```

</p></details>

---

```shell script
C:/MinGW/bin/gcc.exe -shared -o c:\path\mylib.dll c:\path\script.c
```
