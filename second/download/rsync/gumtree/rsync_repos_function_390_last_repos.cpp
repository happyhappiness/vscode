int _Insure_trap_error(int a1, int a2, int a3, int a4, int a5, int a6)
{
	static int (*fn)();
	int ret, pid_int = getpid();
	char *cmd;

	if (asprintf(&cmd,
	    "/usr/X11R6/bin/xterm -display :0 -T Panic -n Panic -e /bin/sh -c 'cat /tmp/ierrs.*.%d ; "
	    "gdb /proc/%d/exe %d'", pid_int, pid_int, pid_int) < 0)
		return -1;

	if (!fn) {
		static void *h;
		h = dlopen("/usr/local/parasoft/insure++lite/lib.linux2/libinsure.so", RTLD_LAZY);
		fn = dlsym(h, "_Insure_trap_error");
	}

	ret = fn(a1, a2, a3, a4, a5, a6);

	system(cmd);

	free(cmd);

	return ret;
}