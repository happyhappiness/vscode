static char *get_pathname(void)
{
	static char pathname_array[4][PATH_MAX];
	static int index;
	return pathname_array[3 & ++index];
}