static void child_error_fn(const char *err, va_list params)
{
	const char msg[] = "error() should not be called in child\n";
	xwrite(2, msg, sizeof(msg) - 1);
}