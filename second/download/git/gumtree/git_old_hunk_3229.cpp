	else
		*obj = NULL;
	return buf;
}

static int grab_objectname(const char *name, const unsigned char *sha1,
			    struct atom_value *v)
{
	if (!strcmp(name, "objectname")) {
		v->s = xstrdup(sha1_to_hex(sha1));
		return 1;
	}
	if (!strcmp(name, "objectname:short")) {
		v->s = xstrdup(find_unique_abbrev(sha1, DEFAULT_ABBREV));
		return 1;
	}
	return 0;
}

/* See grab_values */
static void grab_common_values(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	int i;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i];
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (!strcmp(name, "objecttype"))
			v->s = typename(obj->type);
		else if (!strcmp(name, "objectsize")) {
			v->ul = sz;
			v->s = xstrfmt("%lu", sz);
		}
		else if (deref)
			grab_objectname(name, obj->oid.hash, v);
	}
}

/* See grab_values */
static void grab_tag_values(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	int i;
	struct tag *tag = (struct tag *) obj;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i];
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (!strcmp(name, "tag"))
