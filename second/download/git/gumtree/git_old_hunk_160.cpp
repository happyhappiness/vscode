	cld.out = dup(incoming);

	if (start_command(&cld))
		logerror("unable to fork");
	else
		add_child(&cld, addr, addrlen);
	close(incoming);
}

static void child_handler(int signo)
{
	/*
	 * Otherwise empty handler because systemcalls will get interrupted
