			    unsigned char prev[20],
			    char *ref,
			    int ref_size,
			    int force)
{
	if (snprintf(ref, ref_size,
		     "%s%s", git_replace_ref_base,
		     sha1_to_hex(object)) > ref_size - 1)
		die("replace ref name too long: %.*s...", 50, ref);
	if (check_refname_format(ref, 0))
		die("'%s' is not a valid ref name.", ref);

	if (read_ref(ref, prev))
