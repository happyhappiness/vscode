static NORETURN void die_builtin(const char *err, va_list params)
{
	vreportf("fatal: ", err, params);
	exit(128);
}