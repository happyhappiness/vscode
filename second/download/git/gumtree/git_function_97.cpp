static NORETURN void die_startup()
{
	fputs("fatal: not enough memory for initialization", stderr);
	exit(128);
}