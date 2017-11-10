static void show_pre_context(struct grep_opt *opt, struct grep_source *gs,
			     char *bol, char *end, unsigned lno)
{
	unsigned cur = lno, from = 1, funcname_lno = 0;
	int funcname_needed = !!opt->funcname;

	if (opt->funcbody && !match_funcname(opt, gs, bol, end))
		funcname_needed = 2;

	if (opt->pre_context < lno)
		from = lno - opt->pre_context;
	if (from <= opt->last_shown)
		from = opt->last_shown + 1;

	/* Rewind. */
	while (bol > gs->buf &&
	       cur > (funcname_needed == 2 ? opt->last_shown + 1 : from)) {
		char *eol = --bol;

		while (bol > gs->buf && bol[-1] != '\n')
			bol--;
		cur--;
		if (funcname_needed && match_funcname(opt, gs, bol, eol)) {
			funcname_lno = cur;
			funcname_needed = 0;
		}
	}

	/* We need to look even further back to find a function signature. */
	if (opt->funcname && funcname_needed)
		show_funcname_line(opt, gs, bol, cur);

	/* Back forward. */
	while (cur < lno) {
		char *eol = bol, sign = (cur == funcname_lno) ? '=' : '-';

		while (*eol != '\n')
			eol++;
		show_line(opt, bol, eol, gs->name, cur, sign);
		bol = eol + 1;
		cur++;
	}
}