static void udt_kill_transfer(struct unidirectional_transfer *t)
{
	t->state = SSTATE_FINISHED;
	/*
	 * Socket read end left open isn't a disaster if nobody
	 * attempts to read from it (mingw compat headers do not
	 * have SHUT_RD)...
	 *
	 * We can't fully close the socket since otherwise gtp
	 * task would first close the socket it sends data to
	 * while closing the ptg file descriptors.
	 */
	if (!t->src_is_sock)
		close(t->src);
	if (t->dest_is_sock)
		shutdown(t->dest, SHUT_WR);
	else
		close(t->dest);
}