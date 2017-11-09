static int show_flag(const char *arg)
{
	if (!(filter & DO_FLAGS))
		return 0;
	if (filter & (is_rev_argument(arg) ? DO_REVS : DO_NOREV)) {
		show(arg);
		return 1;
	}
	return 0;
}