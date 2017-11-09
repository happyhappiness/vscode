static void grab_commit_values(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	int i;
	struct commit *commit = (struct commit *) obj;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i].name;
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (!strcmp(name, "tree")) {
			v->s = xstrdup(oid_to_hex(&commit->tree->object.oid));
		}
		else if (!strcmp(name, "numparent")) {
			v->value = commit_list_count(commit->parents);
			v->s = xstrfmt("%lu", (unsigned long)v->value);
		}
		else if (!strcmp(name, "parent")) {
			struct commit_list *parents;
			struct strbuf s = STRBUF_INIT;
			for (parents = commit->parents; parents; parents = parents->next) {
				struct commit *parent = parents->item;
				if (parents != commit->parents)
					strbuf_addch(&s, ' ');
				strbuf_addstr(&s, oid_to_hex(&parent->object.oid));
			}
			v->s = strbuf_detach(&s, NULL);
		}
	}
}