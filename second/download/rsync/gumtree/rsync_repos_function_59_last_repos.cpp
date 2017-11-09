static inline char *
human_num(int64 num)
{
	extern int human_readable;
	return do_big_num(num, human_readable, NULL);
}