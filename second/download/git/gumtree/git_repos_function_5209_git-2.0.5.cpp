static void init(void)
{
	CONSOLE_SCREEN_BUFFER_INFO sbi;

	static int initialized = 0;
	if (initialized)
		return;

	console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (console == INVALID_HANDLE_VALUE)
		console = NULL;

	if (!console)
		return;

	GetConsoleScreenBufferInfo(console, &sbi);
	attr = plain_attr = sbi.wAttributes;
	negative = 0;

	initialized = 1;
}