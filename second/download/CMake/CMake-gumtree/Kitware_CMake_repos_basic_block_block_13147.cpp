{
	struct tm tm;
	time_t t = 0;
	int64_t data;

	memset(&tm, 0, sizeof(tm));
	if (n != 20)
		return (t);
	data = atol10(p, 4);
	if (data < 1900)
		return (t);
	tm.tm_year = (int)data - 1900;
	p += 4;
	if (*p++ != '-')
		return (t);
	data = atol10(p, 2);
	if (data < 1 || data > 12)
		return (t);
	tm.tm_mon = (int)data -1;
	p += 2;
	if (*p++ != '-')
		return (t);
	data = atol10(p, 2);
	if (data < 1 || data > 31)
		return (t);
	tm.tm_mday = (int)data;
	p += 2;
	if (*p++ != 'T')
		return (t);
	data = atol10(p, 2);
	if (data < 0 || data > 23)
		return (t);
	tm.tm_hour = (int)data;
	p += 2;
	if (*p++ != ':')
		return (t);
	data = atol10(p, 2);
	if (data < 0 || data > 59)
		return (t);
	tm.tm_min = (int)data;
	p += 2;
	if (*p++ != ':')
		return (t);
	data = atol10(p, 2);
	if (data < 0 || data > 60)
		return (t);
	tm.tm_sec = (int)data;
#if 0
	p += 2;
	if (*p != 'Z')
		return (t);
#endif

	t = time_from_tm(&tm);

	return (t);
}