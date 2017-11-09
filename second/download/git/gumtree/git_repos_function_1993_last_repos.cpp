static struct tm *time_to_tm_local(timestamp_t time)
{
	time_t t = time;
	return localtime(&t);
}