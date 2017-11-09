static inline char *
big_dnum(double dnum, int decimal_digits)
{
	return do_big_dnum(dnum, 0, decimal_digits);
}