static void grab_common_values(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	int i;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i].name;
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (!strcmp(name, "objecttype"))
			v->s = typename(obj->type);
		else if (!strcmp(name, "objectsize")) {
			v->value = sz;
			v->s = xstrfmt("%lu", sz);
		}
		else if (deref)
			grab_objectname(name, obj->oid.hash, v, &used_atom[i]);
	}
}