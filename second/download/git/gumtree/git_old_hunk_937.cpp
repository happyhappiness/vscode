	if (!n->generation)
		return n->tip_name;
	else {
		int len = strlen(n->tip_name);
		if (len > 2 && !strcmp(n->tip_name + len - 2, "^0"))
			len -= 2;
		snprintf(buffer, sizeof(buffer), "%.*s~%d", len, n->tip_name,
				n->generation);

		return buffer;
	}
}

static void show_name(const struct object *obj,
		      const char *caller_name,
		      int always, int allow_undefined, int name_only)
{
	const char *name;
	const struct object_id *oid = &obj->oid;

	if (!name_only)
		printf("%s ", caller_name ? caller_name : oid_to_hex(oid));
	name = get_rev_name(obj);
	if (name)
		printf("%s\n", name);
	else if (allow_undefined)
		printf("undefined\n");
	else if (always)
		printf("%s\n", find_unique_abbrev(oid->hash, DEFAULT_ABBREV));
	else
		die("cannot describe '%s'", oid_to_hex(oid));
}

static char const * const name_rev_usage[] = {
	N_("git name-rev [<options>] <commit>..."),
	N_("git name-rev [<options>] --all"),
	N_("git name-rev [<options>] --stdin"),
	NULL
};

static void name_rev_line(char *p, struct name_ref_data *data)
{
	int forty = 0;
	char *p_start;
	for (p_start = p; *p; p++) {
#define ishex(x) (isdigit((x)) || ((x) >= 'a' && (x) <= 'f'))
		if (!ishex(*p))
			forty = 0;
