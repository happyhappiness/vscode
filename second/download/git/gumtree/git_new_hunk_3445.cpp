	free(pp->pfd);

	/*
	 * When get_next_task added messages to the buffer in its last
	 * iteration, the buffered output is non empty.
	 */
	strbuf_write(&pp->buffered_output, stderr);
	strbuf_release(&pp->buffered_output);

	sigchain_pop_common();
}

/* returns
