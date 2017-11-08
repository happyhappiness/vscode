static void warn_builtin(const char *warn, va_list params)
{
	vreportf("warning: ", warn, params);
}