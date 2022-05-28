#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

static const char *error = NULL;

EXPORT int init(const char *str) {
	return 1;
}

EXPORT const char *getLastError() { 
	return error;
}

EXPORT int eval(const char *func,
	int nArgs,              // <--- Number of arguments given
	const double **inReal,  // <--- Matrix of real part of arguments
	const double **inImag,  // <--- Matrix of imag part of arguments
	int blockSize,          // <--- Length of columns with arguments
	double *outReal,        // <--- Column of real part of output
	double *outImag) {      // <--- Column of imag part of output
	int i;
	if (strcmp("test_func", func) == 0) { // <--- Check if we call right function from dll
		if (nArgs != 2) {             // <--- Check if we use right number of arguments
			error = "Two argument expected";
			return 0;
		}
		for (i = 0; i < blockSize; i++) { // <--- looping over every value in columns
                        // -------------------------------->MY CODE HERE<--------------------------------
			double a = inReal[0][i];  // <--- take real part of first ([0]) argument.
			double b = inReal[1][i];  // <--- take real part of second ([1]) argument.
			outReal[i] = a^2+b^2;
                        // -------------------------------->MY CODE HERE<--------------------------------
		}

		return 1;
	}
	else {
		error = "Unknown function";
		return 0;
	}
}
