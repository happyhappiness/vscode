static long ff_regexp(const char *line, long len,
		char *buffer, long buffer_size, void *priv)
{
	char *line_buffer;
	struct ff_regs *regs = priv;
	regmatch_t pmatch[2];
	int i;
	int result = -1;

	/* Exclude terminating newline (and cr) from matching */
	if (len > 0 && line[len-1] == '\n') {
		if (len > 1 && line[len-2] == '\r')
			len -= 2;
		else
			len--;
	}

	line_buffer = xstrndup(line, len); /* make NUL terminated */

	for (i = 0; i < regs->nr; i++) {
		struct ff_reg *reg = regs->array + i;
		if (!regexec(&reg->re, line_buffer, 2, pmatch, 0)) {
			if (reg->negate)
				goto fail;
			break;
		}
	}
	if (regs->nr <= i)
		goto fail;
	i = pmatch[1].rm_so >= 0 ? 1 : 0;
	line += pmatch[i].rm_so;
	result = pmatch[i].rm_eo - pmatch[i].rm_so;
	if (result > buffer_size)
		result = buffer_size;
	while (result > 0 && (isspace(line[result - 1])))
		result--;
	memcpy(buffer, line, result);
 fail:
	free(line_buffer);
	return result;
}