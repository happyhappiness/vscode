static void udt_close_if_finished(struct unidirectional_transfer *t)
{
	if (STATE_NEEDS_CLOSING(t->state) && !t->bufuse) {
		t->state = SSTATE_FINISHED;
		if (t->dest_is_sock)
			shutdown(t->dest, SHUT_WR);
		else
			close(t->dest);
		transfer_debug("Closed %s.", t->dest_name);
	}
}