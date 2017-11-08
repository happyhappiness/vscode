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
			v->s = tag->tag;
		else if (!strcmp(name, "type") && tag->tagged)
			v->s = typename(tag->tagged->type);
		else if (!strcmp(name, "object") && tag->tagged) {
			char *s = xmalloc(41);
			strcpy(s, sha1_to_hex(tag->tagged->sha1));
			v->s = s;
		}
	}
}