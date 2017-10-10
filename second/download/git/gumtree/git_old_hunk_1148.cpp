
	if (!err && ctx && ctx->flags & PARSE_OPT_SHELL_EVAL)
		fprintf(outfile, "cat <<\\EOF\n");

	fprintf_ln(outfile, _("usage: %s"), _(*usagestr++));
	while (*usagestr && **usagestr)
		/* TRANSLATORS: the colon here should align with the
		   one in "usage: %s" translation */
		fprintf_ln(outfile, _("   or: %s"), _(*usagestr++));
	while (*usagestr) {
		if (**usagestr)
			fprintf_ln(outfile, _("    %s"), _(*usagestr));
		else
			putchar('\n');
