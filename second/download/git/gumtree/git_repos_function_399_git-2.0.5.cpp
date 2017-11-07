static void lowercase(char *p)
{
	for (; *p; p++)
		*p = tolower(*p);
}