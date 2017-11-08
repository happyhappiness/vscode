int process_exists(int pid)
{
	return(kill(pid,0) == 0 || errno != ESRCH);
}