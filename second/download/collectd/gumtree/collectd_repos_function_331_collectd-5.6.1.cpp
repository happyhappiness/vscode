static int
zone_compare(const void *a, const void *b)
{
	if (*(const zoneid_t *)a == *(const zoneid_t *)b)
		return(0);
	if (*(const zoneid_t *)a < *(const zoneid_t *)b)
		return(-1);
	return(1);
}