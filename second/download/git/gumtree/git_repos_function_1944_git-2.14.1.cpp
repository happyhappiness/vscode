static long ff_regexp(const char *line, long len,
		char *buffer, long buffer_size, void *priv)
{
	struct ff_regs *regs = priv;
	regmatch_t pmatch[2];
	int i;
	int result;

	/* Exclude terminating newline (and cr) from matching */
	if (len > 0 && line[len-1] == '\n') {
		if (len > 1 && line[len-2] == '\r')
			len -= 2;
		else
			len--;
	}

	for (i = 0; i < regs->nr; i++) {
		struct ff_reg *reg = regs->array + i;
		if (!regexec_buf(&reg->re, line, len, 2, pmatch, 0)) {
			if (reg->negate)
				return -1;
			break;
		}
	}
	if (regs->nr <= i)
		return -1;
	i = pmatch[1].rm_so >= 0 ? 1 : 0;
	line += pmatch[i].rm_so;
	result = pmatch[i].rm_eo - pmatch[i].rm_so;
	if (result > buffer_size)
		result = buffer_size;
	while (result > 0 && (isspace(line[result - 1])))
		result--;
	memcpy(buffer, line, result);
	return result;
}