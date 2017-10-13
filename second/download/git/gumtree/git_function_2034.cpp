static NORETURN void die_child(const char *err, va_list params)
{
	vwritef(child_err, "fatal: ", err, params);
	exit(128);
}