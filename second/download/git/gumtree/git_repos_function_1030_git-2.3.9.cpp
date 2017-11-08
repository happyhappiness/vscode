static void emit_rewrite_lines(struct emit_callback *ecb,
			       int prefix, const char *data, int size)
{
	const char *endp = NULL;
	static const char *nneof = " No newline at end of file\n";
	const char *old = diff_get_color(ecb->color_diff, DIFF_FILE_OLD);
	const char *reset = diff_get_color(ecb->color_diff, DIFF_RESET);

	while (0 < size) {
		int len;

		endp = memchr(data, '\n', size);
		len = endp ? (endp - data + 1) : size;
		if (prefix != '+') {
			ecb->lno_in_preimage++;
			emit_line_0(ecb->opt, old, reset, '-',
				    data, len);
		} else {
			ecb->lno_in_postimage++;
			emit_add_line(reset, ecb, data, len);
		}
		size -= len;
		data += len;
	}
	if (!endp) {
		const char *plain = diff_get_color(ecb->color_diff,
						   DIFF_PLAIN);
		putc('\n', ecb->opt->file);
		emit_line_0(ecb->opt, plain, reset, '\\',
			    nneof, strlen(nneof));
	}
}