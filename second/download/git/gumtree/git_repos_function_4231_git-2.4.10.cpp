static void grab_commit_values(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	int i;
	struct commit *commit = (struct commit *) obj;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i];
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (!strcmp(name, "tree")) {
			char *s = xmalloc(41);
			strcpy(s, sha1_to_hex(commit->tree->object.sha1));
			v->s = s;
		}
		if (!strcmp(name, "numparent")) {
			char *s = xmalloc(40);
			v->ul = commit_list_count(commit->parents);
			sprintf(s, "%lu", v->ul);
			v->s = s;
		}
		else if (!strcmp(name, "parent")) {
			int num = commit_list_count(commit->parents);
			int i;
			struct commit_list *parents;
			char *s = xmalloc(41 * num + 1);
			v->s = s;
			for (i = 0, parents = commit->parents;
			     parents;
			     parents = parents->next, i = i + 41) {
				struct commit *parent = parents->item;
				strcpy(s+i, sha1_to_hex(parent->object.sha1));
				if (parents->next)
					s[i+40] = ' ';
			}
			if (!i)
				*s = '\0';
		}
	}
}