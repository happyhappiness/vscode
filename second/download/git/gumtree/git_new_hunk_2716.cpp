	 * Most hints are counter-productive when the commit has
	 * already started.
	 */
	s->hints = 0;

	if (clean_message_contents)
		strbuf_stripspace(&sb, 0);

	if (signoff)
		append_signoff(&sb, ignore_non_trailer(&sb), 0);

	if (fwrite(sb.buf, 1, sb.len, s->fp) < sb.len)
		die_errno(_("could not write commit template"));
