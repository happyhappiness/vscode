static void pp_cleanup(struct parallel_processes *pp)
{
	int i;

	trace_printf("run_processes_parallel: done");
	for (i = 0; i < pp->max_processes; i++) {
		strbuf_release(&pp->children[i].err);
		child_process_clear(&pp->children[i].process);
	}

	free(pp->children);
	free(pp->pfd);

	/*
	 * When get_next_task added messages to the buffer in its last
	 * iteration, the buffered output is non empty.
	 */
	fputs(pp->buffered_output.buf, stderr);
	strbuf_release(&pp->buffered_output);

	sigchain_pop_common();
}