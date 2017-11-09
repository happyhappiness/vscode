static void NORETURN child_die_fn(const char *err, va_list params)
{
	const char msg[] = "die() should not be called in child\n";
	xwrite(2, msg, sizeof(msg) - 1);
	_exit(2);
}