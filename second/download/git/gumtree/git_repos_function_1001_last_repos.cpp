int git_atexit(void (*handler)(void))
{
	ALLOC_GROW(git_atexit_hdlrs.handlers, git_atexit_hdlrs.nr + 1, git_atexit_hdlrs.alloc);
	git_atexit_hdlrs.handlers[git_atexit_hdlrs.nr++] = handler;
	if (!git_atexit_installed) {
		if (atexit(&git_atexit_dispatch))
			return -1;
		git_atexit_installed = 1;
	}
	return 0;
}