static void git_atexit_clear(void)
{
	free(git_atexit_hdlrs.handlers);
	memset(&git_atexit_hdlrs, 0, sizeof(git_atexit_hdlrs));
	git_atexit_installed = 0;
}