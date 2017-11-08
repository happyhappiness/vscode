static void date_yesterday(struct tm *tm, struct tm *now, int *num)
{
	update_tm(tm, now, 24*60*60);
}