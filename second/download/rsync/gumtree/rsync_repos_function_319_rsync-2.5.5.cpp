void wait_process(pid_t pid, int *status)
{
	while (waitpid(pid, status, WNOHANG) == 0) {
		msleep(20);
		io_flush();
	}
        
        /* TODO: If the child exited on a signal, then log an
         * appropriate error message.  Perhaps we should also accept a
         * message describing the purpose of the child.  Also indicate
         * this to the caller so that thhey know something went
         * wrong.  */
	*status = WEXITSTATUS(*status);
}