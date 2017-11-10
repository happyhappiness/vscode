static void date_never(struct tm *tm, struct tm *now, int *num)
{
	time_t n = 0;
	localtime_r(&n, tm);
}