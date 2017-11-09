void xdiff_set_find_func(xdemitconf_t *xecfg, const char *value, int cflags)
{
	int i;
	struct ff_regs *regs;

	xecfg->find_func = ff_regexp;
	regs = xecfg->find_func_priv = xmalloc(sizeof(struct ff_regs));
	for (i = 0, regs->nr = 1; value[i]; i++)
		if (value[i] == '\n')
			regs->nr++;
	ALLOC_ARRAY(regs->array, regs->nr);
	for (i = 0; i < regs->nr; i++) {
		struct ff_reg *reg = regs->array + i;
		const char *ep = strchr(value, '\n'), *expression;
		char *buffer = NULL;

		reg->negate = (*value == '!');
		if (reg->negate && i == regs->nr - 1)
			die("Last expression must not be negated: %s", value);
		if (*value == '!')
			value++;
		if (ep)
			expression = buffer = xstrndup(value, ep - value);
		else
			expression = value;
		if (regcomp(&reg->re, expression, cflags))
			die("Invalid regexp to look for hunk header: %s", expression);
		free(buffer);
		value = ep + 1;
	}
}