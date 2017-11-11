static void grab_date(const char *buf, struct atom_value *v, const char *atomname)
{
	const char *eoemail = strstr(buf, "> ");
	char *zone;
	unsigned long timestamp;
	long tz;
	enum date_mode date_mode = DATE_NORMAL;
	const char *formatp;

	/*
	 * We got here because atomname ends in "date" or "date<something>";
	 * it's not possible that <something> is not ":<format>" because
	 * parse_atom() wouldn't have allowed it, so we can assume that no
	 * ":" means no format is specified, and use the default.
	 */
	formatp = strchr(atomname, ':');
	if (formatp != NULL) {
		formatp++;
		date_mode = parse_date_format(formatp);
	}

	if (!eoemail)
		goto bad;
	timestamp = strtoul(eoemail + 2, &zone, 10);
	if (timestamp == ULONG_MAX)
		goto bad;
	tz = strtol(zone, NULL, 10);
	if ((tz == LONG_MIN || tz == LONG_MAX) && errno == ERANGE)
		goto bad;
	v->s = xstrdup(show_date(timestamp, tz, date_mode));
	v->ul = timestamp;
	return;
 bad:
	v->s = "";
	v->ul = 0;
}