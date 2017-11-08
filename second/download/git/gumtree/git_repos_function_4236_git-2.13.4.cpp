static void show_line(struct grep_opt *opt, char *bol, char *eol,
		      const char *name, unsigned lno, char sign)
{
	int rest = eol - bol;
	const char *match_color, *line_color = NULL;

	if (opt->file_break && opt->last_shown == 0) {
		if (opt->show_hunk_mark)
			opt->output(opt, "\n", 1);
	} else if (opt->pre_context || opt->post_context || opt->funcbody) {
		if (opt->last_shown == 0) {
			if (opt->show_hunk_mark) {
				output_color(opt, "--", 2, opt->color_sep);
				opt->output(opt, "\n", 1);
			}
		} else if (lno > opt->last_shown + 1) {
			output_color(opt, "--", 2, opt->color_sep);
			opt->output(opt, "\n", 1);
		}
	}
	if (opt->heading && opt->last_shown == 0) {
		output_color(opt, name, strlen(name), opt->color_filename);
		opt->output(opt, "\n", 1);
	}
	opt->last_shown = lno;

	if (!opt->heading && opt->pathname) {
		output_color(opt, name, strlen(name), opt->color_filename);
		output_sep(opt, sign);
	}
	if (opt->linenum) {
		char buf[32];
		xsnprintf(buf, sizeof(buf), "%d", lno);
		output_color(opt, buf, strlen(buf), opt->color_lineno);
		output_sep(opt, sign);
	}
	if (opt->color) {
		regmatch_t match;
		enum grep_context ctx = GREP_CONTEXT_BODY;
		int ch = *eol;
		int eflags = 0;

		if (sign == ':')
			match_color = opt->color_match_selected;
		else
			match_color = opt->color_match_context;
		if (sign == ':')
			line_color = opt->color_selected;
		else if (sign == '-')
			line_color = opt->color_context;
		else if (sign == '=')
			line_color = opt->color_function;
		*eol = '\0';
		while (next_match(opt, bol, eol, ctx, &match, eflags)) {
			if (match.rm_so == match.rm_eo)
				break;

			output_color(opt, bol, match.rm_so, line_color);
			output_color(opt, bol + match.rm_so,
				     match.rm_eo - match.rm_so, match_color);
			bol += match.rm_eo;
			rest -= match.rm_eo;
			eflags = REG_NOTBOL;
		}
		*eol = ch;
	}
	output_color(opt, bol, rest, line_color);
	opt->output(opt, "\n", 1);
}