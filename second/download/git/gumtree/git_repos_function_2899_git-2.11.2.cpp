static void stop_multi_file_filter(struct child_process *process)
{
	sigchain_push(SIGPIPE, SIG_IGN);
	/* Closing the pipe signals the filter to initiate a shutdown. */
	close(process->in);
	close(process->out);
	sigchain_pop(SIGPIPE);
	/* Finish command will wait until the shutdown is complete. */
	finish_command(process);
}