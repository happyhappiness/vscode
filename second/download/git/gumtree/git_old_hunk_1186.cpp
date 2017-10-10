	va_list params;

	va_start(params, warn);
	warn_routine(warn, params);
	va_end(params);
}
