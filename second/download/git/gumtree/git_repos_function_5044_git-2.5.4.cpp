static int index_output_cb(const struct option *opt, const char *arg,
				 int unset)
{
	set_alternate_index_output(arg);
	return 0;
}