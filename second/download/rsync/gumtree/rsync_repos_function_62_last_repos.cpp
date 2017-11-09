static inline char *
human_dnum(double dnum, int decimal_digits)
{
	extern int human_readable;
	return do_big_dnum(dnum, human_readable, decimal_digits);
}