static void grab_sub_body_contents(struct atom_value *val, int deref, struct object *obj, void *buf, unsigned long sz)
{
	int i;
	const char *subpos = NULL, *bodypos = NULL, *sigpos = NULL;
	unsigned long sublen = 0, bodylen = 0, nonsiglen = 0, siglen = 0;

	for (i = 0; i < used_atom_cnt; i++) {
		const char *name = used_atom[i];
		struct atom_value *v = &val[i];
		if (!!deref != (*name == '*'))
			continue;
		if (deref)
			name++;
		if (strcmp(name, "subject") &&
		    strcmp(name, "body") &&
		    strcmp(name, "contents") &&
		    strcmp(name, "contents:subject") &&
		    strcmp(name, "contents:body") &&
		    strcmp(name, "contents:signature"))
			continue;
		if (!subpos)
			find_subpos(buf, sz,
				    &subpos, &sublen,
				    &bodypos, &bodylen, &nonsiglen,
				    &sigpos, &siglen);

		if (!strcmp(name, "subject"))
			v->s = copy_subject(subpos, sublen);
		else if (!strcmp(name, "contents:subject"))
			v->s = copy_subject(subpos, sublen);
		else if (!strcmp(name, "body"))
			v->s = xmemdupz(bodypos, bodylen);
		else if (!strcmp(name, "contents:body"))
			v->s = xmemdupz(bodypos, nonsiglen);
		else if (!strcmp(name, "contents:signature"))
			v->s = xmemdupz(sigpos, siglen);
		else if (!strcmp(name, "contents"))
			v->s = xstrdup(subpos);
	}
}