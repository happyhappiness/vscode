static int header_callback(const struct option *opt, const char *arg, int unset)
{
	if (unset) {
		string_list_clear(&extra_hdr, 0);
		string_list_clear(&extra_to, 0);
		string_list_clear(&extra_cc, 0);
	} else {
	    add_header(arg);
	}
	return 0;
}