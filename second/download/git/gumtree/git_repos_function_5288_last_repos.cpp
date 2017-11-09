static void show_with_type(int type, const char *arg)
{
	if (type != show_type)
		putchar('^');
	show(arg);
}