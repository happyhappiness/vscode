static void *udt_copy_task_routine(void *udt)
{
	struct unidirectional_transfer *t = (struct unidirectional_transfer *)udt;
	while (t->state != SSTATE_FINISHED) {
		if (STATE_NEEDS_READING(t->state))
			if (udt_do_read(t))
				return NULL;
		if (STATE_NEEDS_WRITING(t->state))
			if (udt_do_write(t))
				return NULL;
		if (STATE_NEEDS_CLOSING(t->state))
			udt_close_if_finished(t);
	}
	return udt;	/* Just some non-NULL value. */
}