static int format_reflog_person(struct strbuf *sb,
				char part,
				struct reflog_walk_info *log,
				const struct date_mode *dmode)
{
	const char *ident;

	if (!log)
		return 2;

	ident = get_reflog_ident(log);
	if (!ident)
		return 2;

	return format_person_part(sb, part, ident, strlen(ident), dmode);
}