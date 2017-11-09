static void add_work(struct grep_opt *opt, enum grep_source_type type,
		     const char *name, const char *path, const void *id)
{
	grep_lock();

	while ((todo_end+1) % ARRAY_SIZE(todo) == todo_done) {
		pthread_cond_wait(&cond_write, &grep_mutex);
	}

	grep_source_init(&todo[todo_end].source, type, name, path, id);
	if (opt->binary != GREP_BINARY_TEXT)
		grep_source_load_driver(&todo[todo_end].source);
	todo[todo_end].done = 0;
	strbuf_reset(&todo[todo_end].out);
	todo_end = (todo_end + 1) % ARRAY_SIZE(todo);

	pthread_cond_signal(&cond_add);
	grep_unlock();
}