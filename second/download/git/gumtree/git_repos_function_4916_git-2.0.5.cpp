static void hash_stdin_paths(const char *type, int write_objects)
{
	struct strbuf buf = STRBUF_INIT, nbuf = STRBUF_INIT;

	while (strbuf_getline(&buf, stdin, '\n') != EOF) {
		if (buf.buf[0] == '"') {
			strbuf_reset(&nbuf);
			if (unquote_c_style(&nbuf, buf.buf, NULL))
				die("line is badly quoted");
			strbuf_swap(&buf, &nbuf);
		}
		hash_object(buf.buf, type, write_objects,
		    no_filters ? NULL : buf.buf);
	}
	strbuf_release(&buf);
	strbuf_release(&nbuf);
}