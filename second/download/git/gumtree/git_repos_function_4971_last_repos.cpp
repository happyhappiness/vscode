static int verify_tag(const char *name, const char *ref,
		      const struct object_id *oid, const void *cb_data)
{
	int flags;
	const struct ref_format *format = cb_data;
	flags = GPG_VERIFY_VERBOSE;

	if (format->format)
		flags = GPG_VERIFY_OMIT_STATUS;

	if (gpg_verify_tag(oid->hash, name, flags))
		return -1;

	if (format->format)
		pretty_print_ref(name, oid->hash, format);

	return 0;
}