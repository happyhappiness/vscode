static void show_funcname_line(struct grep_opt *opt, struct grep_source *gs,
			       char *bol, unsigned lno)
{
	while (bol > gs->buf) {
		char *eol = --bol;

		while (bol > gs->buf && bol[-1] != '\n')
			bol--;
		lno--;

		if (lno <= opt->last_shown)
			break;

		if (match_funcname(opt, gs, bol, eol)) {
			show_line(opt, bol, eol, gs->name, lno, '=');
			break;
		}
	}
}