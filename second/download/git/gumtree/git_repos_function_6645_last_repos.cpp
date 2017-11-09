struct tm *git_gmtime(const time_t *timep)
{
	static struct tm result;
	return git_gmtime_r(timep, &result);
}