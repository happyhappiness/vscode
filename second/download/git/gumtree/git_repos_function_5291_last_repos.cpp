static int show_default(void)
{
	const char *s = def;

	if (s) {
		struct object_id oid;

		def = NULL;
		if (!get_oid(s, &oid)) {
			show_rev(NORMAL, &oid, s);
			return 1;
		}
	}
	return 0;
}