int walker_targets_stdin(char ***target, const char ***write_ref)
{
	int targets = 0, targets_alloc = 0;
	struct strbuf buf = STRBUF_INIT;
	*target = NULL; *write_ref = NULL;
	while (1) {
		char *rf_one = NULL;
		char *tg_one;

		if (strbuf_getline(&buf, stdin, '\n') == EOF)
			break;
		tg_one = buf.buf;
		rf_one = strchr(tg_one, '\t');
		if (rf_one)
			*rf_one++ = 0;

		if (targets >= targets_alloc) {
			targets_alloc = targets_alloc ? targets_alloc * 2 : 64;
			REALLOC_ARRAY(*target, targets_alloc);
			REALLOC_ARRAY(*write_ref, targets_alloc);
		}
		(*target)[targets] = xstrdup(tg_one);
		(*write_ref)[targets] = xstrdup_or_null(rf_one);
		targets++;
	}
	strbuf_release(&buf);
	return targets;
}