# Comsol External Functions
Explanation how to use ```External``` comsol node with Dynamic Link Libraries (DLL's) written on C from scratch.

This guide written 27.05.2022 for 5.5 version of Comsol for Windows.\
I found [official version](https://doc.comsol.com/5.5/doc/com.comsol.help.comsol/comsol_ref_definitions.12.047.html) of doc's with External node very poor exlaining how to make it work.

# What do you need to create you own DLL written on C?
1. C program
2. Compiler

---

<details>
<summary><h2>Install compiler. (Click to expand)</h2></summary>
<p>

Website mingw.org does not work anymore, but we can download installer [here](https://sourceforge.net/projects/mingw/).\
Also I keep a copy of installer at the repository [mingw-get-setup.exe](https://github.com/byquip/Comsol-External-Functions/blob/main/res/mingw-get-setup.exe).

1. Launch installer.\
![Launch installer](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_1.png)

2. Set path or keep as it is.\
![Set path or keep as it is.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_2.png)

3. Wait for manager installed.\
![Wait for manager installed.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_3.png)

4. Right-click on the line which you need to install and choose "Mark for installation".\
![Right-click on the line which you need to install and choose "Mark for installation".](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_4.png)

5. Select marked lines.\
![Select marked lines.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_5.png)

6. Click "Installation" and then "Apply changes".\
![Click "Installation" and then "Apply changes".](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_6.png)

7. Click "Apply" again.\
![Click "Apply" again.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_7.png)

8. Make sure that you have green squares in front of each selected line.\
![Make sure that you have green squares in front of each selected line.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/mingw_s_8.png)

Last thing it's toset environment variables.
In Windows CMD prompt write next
```shell script
set PATH=C:\mingw;C:\mingw\bin;%PATH%
```
check if environment variables setted
```shell script
echo %PATH%
```
</p></details>

---

<details>
<summary><h2>Prepere C code (Click to expand)</h2></summary>
<p>
  Slide 7 of Presentation from cern website for materials[2] link in the end.	
  Code example [here](https://github.com/byquip/Comsol-External-Functions/blob/main/res/script.c).
  
  This is basic example eqivalent to ```sin(a^2+b^2)/(a^2+b^2)``` but in Comsol it will be used like ```test_func(x, y)```

```c script
// Libs which necessary
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER                      // DO NOT TOUCH
#define EXPORT __declspec(dllexport) // DO NOT TOUCH
#else                                // DO NOT TOUCH
#define EXPORT                       // DO NOT TOUCH
#endif                               // DO NOT TOUCH

static const char *error = NULL;     // DO NOT TOUCH

EXPORT int init(const char *str) {   // DO NOT TOUCH (initialisation)
	return 1;                    // DO NOT TOUCH
}                                    // DO NOT TOUCH

EXPORT const char *getLastError() {  // DO NOT TOUCH (errors handler)
	return error;                // DO NOT TOUCH
}                                    // DO NOT TOUCH

EXPORT int eval(const char *func, // <--- Name of function given
	int nArgs,                // <--- Number of arguments given
	const double **inReal,    // <--- Matrix of real part of arguments
	const double **inImag,    // <--- Matrix of imag part of arguments
	int blockSize,            // <--- Length of columns with arguments
	double *outReal,          // <--- Column of real part of output
	double *outImag) {        // <--- Column of imag part of output
	int i;
	if (strcmp("test_func", func) == 0) { // <--- Check if we call right function from dll
		if (nArgs != 2) {             // <--- Check if we use right number of arguments
			error = "Two argument expected";
			return 0;
		}
		for (i = 0; i < blockSize; i++) { // <--- looping over every value in columns
                        // ------------------------------------>MY CODE HERE<------------------------------------
			double a = inReal[0][i];             // <--- take real part of first ([0]) argument.
			double b = inReal[1][i];             // <--- take real part of second ([1]) argument.
			outReal[i] = sin(a*a+b*b)/(a*a+b*b); // <--- solve and assign to real part of the output
                        // ------------------------------------>MY CODE HERE<------------------------------------
		}

		return 1;
	}
	else {
		error = "Unknown function";
		return 0;
	}
}
```
                              
</p></details>

---
  
<details>
<summary><h2>Compile C code (Click to expand)</h2></summary>
<p>
For compiling we use installed utillity.<br>
In Windows CMD prompt write next (open new):
  
```shell script
gcc -shared -o c:\mypath\mylib.dll c:\mypath\script.c
```
  
at path ```c:\mypath``` suppose to appeear ```mylib.dll```
</p></details>
  
---
  
<details>
<summary><h2>Usage of created DLL (Click to expand)</h2></summary>
<p>
  
The file saved to repository [Example.mph](https://github.com/byquip/Comsol-External-Functions/blob/main/res/Example.mph)
  
0. Make sure you allowed to run external libraries at ```Preferences```.\
![Make sure you allowed to run external libraries.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/comsol_s_4.png)

1. Create ```External``` node.\
![Create External node](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/comsol_s_1.png)

2. Select path to ```mylib.dll``` and indicate function name which we used in ```script.c``` on line 30 ```test_func``` and 2 arguments which this function take.\
![Select path to DLL](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/comsol_s_2.png)

3. Usage is the same as with any other comsol function.\
![Usage is the same as with any other comsol function.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/comsol_s_5.png)
  
4. As any other comsol function you can plot it.\
  For this you need to indicate range of values for each argument at ``` Plot Preferences```.\
  Then press ```Plot```.\
  **WARNING!** <ins>plot complicated function could compleately freeze your comsol project. Better to test it first on blanc file.</ins>
![As any other comsol function you can plot it.](https://github.com/byquip/Comsol-External-Functions/blob/main/pictures/comsol_s_3.png)
  
</p></details>
 
Author: Kostiantyn Vasko\
Sources:
1. [Comsol unsolved forum problem](https://www.comsol.com/forum/thread/122051/error-while-calling-external-c-function)
2. [Presentation from cern website for materials](indico.cern.ch/event/796548/contributions/3453461/attachments/1857604%2F3051719/SteamWorkshopYoussef_MM.pptx&usg=AOvVaw0erN1NfV535XbVFO5pqTPM)\
	On 7 slide of this Power Point linked some paper:\
	L. Bortot, USE OF EXTERNAL C FUNCTIONS  IN COMSOL MULTIPHYSICS, p. 11\
	I did not found it.
3. [Some paper from comsol conference](https://www.comsol.it/paper/download/360611/bortot_paper.pdf)
