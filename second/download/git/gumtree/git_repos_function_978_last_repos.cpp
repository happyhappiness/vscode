static void child_warn_fn(const char *err, va_list params)
{
	const char msg[] = "warn() should not be called in child\n";
	xwrite(2, msg, sizeof(msg) - 1);
}