static void emit_rewrite_lines(struct emit_callback *ecb,
			       int prefix, const char *data, int size)
{
	const char *endp = NULL;
	static const char *nneof = " No newline at end of file\n";
	const char *reset = diff_get_color(ecb->color_diff, DIFF_RESET);

	while (0 < size) {
		int len;

		endp = memchr(data, '\n', size);
		len = endp ? (endp - data + 1) : size;
		if (prefix != '+') {
			ecb->lno_in_preimage++;
			emit_del_line(reset, ecb, data, len);
		} else {
			ecb->lno_in_postimage++;
			emit_add_line(reset, ecb, data, len);
		}
		size -= len;
		data += len;
	}
	if (!endp) {
		const char *context = diff_get_color(ecb->color_diff,
						     DIFF_CONTEXT);
		putc('\n', ecb->opt->file);
		emit_line_0(ecb->opt, context, reset, '\\',
			    nneof, strlen(nneof));
	}
}