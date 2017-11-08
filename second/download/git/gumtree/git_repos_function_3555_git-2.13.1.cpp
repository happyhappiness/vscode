static void child_handler(int signo)
{
	/*
	 * Otherwise empty handler because systemcalls will get interrupted
	 * upon signal receipt
	 * SysV needs the handler to be rearmed
	 */
	signal(SIGCHLD, child_handler);
}