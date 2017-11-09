static void work_done(struct work_item *w)
{
	int old_done;

	grep_lock();
	w->done = 1;
	old_done = todo_done;
	for(; todo[todo_done].done && todo_done != todo_start;
	    todo_done = (todo_done+1) % ARRAY_SIZE(todo)) {
		w = &todo[todo_done];
		if (w->out.len) {
			const char *p = w->out.buf;
			size_t len = w->out.len;

			/* Skip the leading hunk mark of the first file. */
			if (skip_first_line) {
				while (len) {
					len--;
					if (*p++ == '\n')
						break;
				}
				skip_first_line = 0;
			}

			write_or_die(1, p, len);
		}
		grep_source_clear(&w->source);
	}

	if (old_done != todo_done)
		pthread_cond_signal(&cond_write);

	if (all_work_added && todo_done == todo_end)
		pthread_cond_signal(&cond_result);

	grep_unlock();
}