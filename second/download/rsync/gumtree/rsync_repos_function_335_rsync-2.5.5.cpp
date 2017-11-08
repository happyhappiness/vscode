static RETSIGTYPE rsync_panic_handler(int UNUSED(whatsig))
{
	char cmd_buf[300];
	int ret;
	sprintf(cmd_buf, 
		"xterm -display :0 -T Panic -n Panic "
		"-e gdb /proc/%d/exe %d", 
		getpid(), getpid());

	/* Unless we failed to execute gdb, we allow the process to
	 * continue.  I'm not sure if that's right. */
	ret = system(cmd_buf);
	if (ret)
		_exit(ret);
}