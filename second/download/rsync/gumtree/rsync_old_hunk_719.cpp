		    if ((opt->argInfo & POPT_ARG_MASK) == POPT_ARG_DOUBLE) {
			*((double *) opt->arg) = aDouble;
		    } else {
#ifndef DBL_EPSILON
#define DBL_EPSILON 2.2204460492503131e-16
#endif
#define _ABS(a)	((((a) - 0.0) < DBL_EPSILON) ? -(a) : (a))
			if ((_ABS(aDouble) - FLT_MAX) > DBL_EPSILON)
			    return POPT_ERROR_OVERFLOW;
			if ((FLT_MIN - _ABS(aDouble)) > DBL_EPSILON)
			    return POPT_ERROR_OVERFLOW;
			*((float *) opt->arg) = aDouble;
		    }
		}   /*@switchbreak@*/ break;
		default:
		    fprintf(stdout,
