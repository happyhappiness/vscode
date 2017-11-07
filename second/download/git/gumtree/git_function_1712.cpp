struct date_mode *date_mode_from_type(enum date_mode_type type)
{
	static struct date_mode mode;
	if (type == DATE_STRFTIME)
		die("BUG: cannot create anonymous strftime date_mode struct");
	mode.type = type;
	return &mode;
}