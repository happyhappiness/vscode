static unsigned parse_score(const char *arg)
{
	char *end;
	unsigned long score = strtoul(arg, &end, 10);
	if (*end)
		return 0;
	return score;
}