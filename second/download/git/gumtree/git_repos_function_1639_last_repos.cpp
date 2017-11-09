static unsigned filter_bit_tst(char status, const struct diff_options *opt)
{
	return opt->filter & filter_bit[(int) status];
}