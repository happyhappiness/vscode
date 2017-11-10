static void git_atexit_dispatch(void)
{
	size_t i;

	for (i=git_atexit_hdlrs.nr ; i ; i--)
		git_atexit_hdlrs.handlers[i-1]();
}