char *timestring(time_t t)
{
	static char TimeBuf[200];
	struct tm *tm = localtime(&t);
	char *p;

#ifdef HAVE_STRFTIME
	strftime(TimeBuf, sizeof TimeBuf - 1, "%Y/%m/%d %H:%M:%S", tm);
#else
	strlcpy(TimeBuf, asctime(tm), sizeof TimeBuf);
#endif

	if ((p = strchr(TimeBuf, '\n')) != NULL)
		*p = '\0';

	return TimeBuf;
}