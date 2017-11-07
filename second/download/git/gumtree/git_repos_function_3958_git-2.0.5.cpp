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
			char *s = xmalloc(40);
			sprintf(s, "%lu", sz);
			v->ul = sz;
			v->s = s;
		}
		else if (deref)
			grab_objectname(name, obj->sha1, v);
	}
}