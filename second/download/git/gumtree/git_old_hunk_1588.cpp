	vreportf("warning: ", warn, params);
}

static int die_is_recursing_builtin(void)
{
	static int dying;
	return dying++;
}

/* If we are in a dlopen()ed .so write to a global variable would segfault
 * (ugh), so keep things static. */
static NORETURN_PTR void (*usage_routine)(const char *err, va_list params) = usage_builtin;
static NORETURN_PTR void (*die_routine)(const char *err, va_list params) = die_builtin;
