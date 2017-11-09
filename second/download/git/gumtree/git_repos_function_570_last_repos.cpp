static void grab_date(const char *buf, struct atom_value *v, const char *atomname)
{
	const char *eoemail = strstr(buf, "> ");
	char *zone;
	timestamp_t timestamp;
	long tz;
	struct date_mode date_mode = { DATE_NORMAL };
	const char *formatp;

	/*
	 * We got here because atomname ends in "date" or "date<something>";
	 * it's not possible that <something> is not ":<format>" because
	 * parse_ref_filter_atom() wouldn't have allowed it, so we can assume that no
	 * ":" means no format is specified, and use the default.
	 */
	formatp = strchr(atomname, ':');
	if (formatp != NULL) {
		formatp++;
		parse_date_format(formatp, &date_mode);
	}

	if (!eoemail)
		goto bad;
	timestamp = parse_timestamp(eoemail + 2, &zone, 10);
	if (timestamp == TIME_MAX)
		goto bad;
	tz = strtol(zone, NULL, 10);
	if ((tz == LONG_MIN || tz == LONG_MAX) && errno == ERANGE)
		goto bad;
	v->s = xstrdup(show_date(timestamp, tz, &date_mode));
	v->value = timestamp;
	return;
 bad:
	v->s = "";
	v->value = 0;
}