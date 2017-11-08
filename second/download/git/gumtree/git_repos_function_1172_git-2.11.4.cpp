static int has_epoch_timestamp(const char *nameline)
{
	/*
	 * We are only interested in epoch timestamp; any non-zero
	 * fraction cannot be one, hence "(\.0+)?" in the regexp below.
	 * For the same reason, the date must be either 1969-12-31 or
	 * 1970-01-01, and the seconds part must be "00".
	 */
	const char stamp_regexp[] =
		"^(1969-12-31|1970-01-01)"
		" "
		"[0-2][0-9]:[0-5][0-9]:00(\\.0+)?"
		" "
		"([-+][0-2][0-9]:?[0-5][0-9])\n";
	const char *timestamp = NULL, *cp, *colon;
	static regex_t *stamp;
	regmatch_t m[10];
	int zoneoffset;
	int hourminute;
	int status;

	for (cp = nameline; *cp != '\n'; cp++) {
		if (*cp == '\t')
			timestamp = cp + 1;
	}
	if (!timestamp)
		return 0;
	if (!stamp) {
		stamp = xmalloc(sizeof(*stamp));
		if (regcomp(stamp, stamp_regexp, REG_EXTENDED)) {
			warning(_("Cannot prepare timestamp regexp %s"),
				stamp_regexp);
			return 0;
		}
	}

	status = regexec(stamp, timestamp, ARRAY_SIZE(m), m, 0);
	if (status) {
		if (status != REG_NOMATCH)
			warning(_("regexec returned %d for input: %s"),
				status, timestamp);
		return 0;
	}

	zoneoffset = strtol(timestamp + m[3].rm_so + 1, (char **) &colon, 10);
	if (*colon == ':')
		zoneoffset = zoneoffset * 60 + strtol(colon + 1, NULL, 10);
	else
		zoneoffset = (zoneoffset / 100) * 60 + (zoneoffset % 100);
	if (timestamp[m[3].rm_so] == '-')
		zoneoffset = -zoneoffset;

	/*
	 * YYYY-MM-DD hh:mm:ss must be from either 1969-12-31
	 * (west of GMT) or 1970-01-01 (east of GMT)
	 */
	if ((zoneoffset < 0 && memcmp(timestamp, "1969-12-31", 10)) ||
	    (0 <= zoneoffset && memcmp(timestamp, "1970-01-01", 10)))
		return 0;

	hourminute = (strtol(timestamp + 11, NULL, 10) * 60 +
		      strtol(timestamp + 14, NULL, 10) -
		      zoneoffset);

	return ((zoneoffset < 0 && hourminute == 1440) ||
		(0 <= zoneoffset && !hourminute));
}