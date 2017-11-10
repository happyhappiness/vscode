const char *show_ident_date(const struct ident_split *ident,
			    enum date_mode mode)
{
	unsigned long date = 0;
	long tz = 0;

	if (ident->date_begin && ident->date_end)
		date = strtoul(ident->date_begin, NULL, 10);
	if (date_overflows(date))
		date = 0;
	else {
		if (ident->tz_begin && ident->tz_end)
			tz = strtol(ident->tz_begin, NULL, 10);
		if (tz >= INT_MAX || tz <= INT_MIN)
			tz = 0;
	}
	return show_date(date, tz, mode);
}