static void error_builtin(const char *err, va_list params)
{
	vreportf("error: ", err, params);
}