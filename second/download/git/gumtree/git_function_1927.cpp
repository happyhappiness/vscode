static void show_name(const struct object *obj,
		      const char *caller_name,
		      int always, int allow_undefined, int name_only)
{
	const char *name;
	const unsigned char *sha1 = obj->sha1;

	if (!name_only)
		printf("%s ", caller_name ? caller_name : sha1_to_hex(sha1));
	name = get_rev_name(obj);
	if (name)
		printf("%s\n", name);
	else if (allow_undefined)
		printf("undefined\n");
	else if (always)
		printf("%s\n", find_unique_abbrev(sha1, DEFAULT_ABBREV));
	else
		die("cannot describe '%s'", sha1_to_hex(sha1));
}