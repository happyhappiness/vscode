static int cmp_ref_sorting(struct ref_sorting *s, struct ref_array_item *a, struct ref_array_item *b)
{
	struct atom_value *va, *vb;
	int cmp;
	cmp_type cmp_type = used_atom[s->atom].type;
	int (*cmp_fn)(const char *, const char *);

	get_ref_atom_value(a, s->atom, &va);
	get_ref_atom_value(b, s->atom, &vb);
	cmp_fn = s->ignore_case ? strcasecmp : strcmp;
	if (s->version)
		cmp = versioncmp(va->s, vb->s);
	else if (cmp_type == FIELD_STR)
		cmp = cmp_fn(va->s, vb->s);
	else {
		if (va->value < vb->value)
			cmp = -1;
		else if (va->value == vb->value)
			cmp = cmp_fn(a->refname, b->refname);
		else
			cmp = 1;
	}

	return (s->reverse) ? -cmp : cmp;
}