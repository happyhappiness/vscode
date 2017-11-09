static inline char *
comma_num(int64 num)
{
	extern int human_readable;
	return do_big_num(num, human_readable != 0, NULL);
}