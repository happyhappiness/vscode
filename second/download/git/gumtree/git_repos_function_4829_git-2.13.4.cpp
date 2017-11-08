static int verify_tag(const char *name, const char *ref,
		      const unsigned char *sha1, const void *cb_data)
{
	int flags;
	const char *fmt_pretty = cb_data;
	flags = GPG_VERIFY_VERBOSE;

	if (fmt_pretty)
		flags = GPG_VERIFY_OMIT_STATUS;

	if (gpg_verify_tag(sha1, name, flags))
		return -1;

	if (fmt_pretty)
		pretty_print_ref(name, sha1, fmt_pretty);

	return 0;
}