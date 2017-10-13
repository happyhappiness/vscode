static void error_child(const char *err, va_list params)
{
	vwritef(child_err, "error: ", err, params);
}