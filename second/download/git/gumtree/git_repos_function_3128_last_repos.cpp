static void parse_push(struct strbuf *buf)
{
	char **specs = NULL;
	int alloc_spec = 0, nr_spec = 0, i, ret;

	do {
		if (starts_with(buf->buf, "push ")) {
			ALLOC_GROW(specs, nr_spec + 1, alloc_spec);
			specs[nr_spec++] = xstrdup(buf->buf + 5);
		}
		else
			die("http transport does not support %s", buf->buf);

		strbuf_reset(buf);
		if (strbuf_getline_lf(buf, stdin) == EOF)
			goto free_specs;
		if (!*buf->buf)
			break;
	} while (1);

	ret = push(nr_spec, specs);
	printf("\n");
	fflush(stdout);

	if (ret)
		exit(128); /* error already reported */

 free_specs:
	for (i = 0; i < nr_spec; i++)
		free(specs[i]);
	free(specs);
}