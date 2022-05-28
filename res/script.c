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
	int nArgs,
	const double **inReal,
	const double **inImag,
	int blockSize,
	double *outReal,
	double *outImag) {
	int i, j;
	if (strcmp("test_func", func) == 0) {
		if (nArgs != 2) {
			error = "Two argument expected";
			return 0;
		}
		for (i = 0; i < blockSize; i++) {
			double a = inReal[0][i];
			double b = inReal[1][i];
			outReal[i] = a^2+b^2;
		}

		return 1;
	}
	else {
		error = "Unknown function";
		return 0;
	}
}
