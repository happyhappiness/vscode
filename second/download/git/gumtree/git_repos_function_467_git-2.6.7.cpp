static int cmp_ref_sorting(struct ref_sorting *s, struct ref_array_item *a, struct ref_array_item *b)
{
	struct atom_value *va, *vb;
	int cmp;
	cmp_type cmp_type = used_atom_type[s->atom];

	get_ref_atom_value(a, s->atom, &va);
	get_ref_atom_value(b, s->atom, &vb);
	switch (cmp_type) {
	case FIELD_STR:
		cmp = strcmp(va->s, vb->s);
		break;
	default:
		if (va->ul < vb->ul)
			cmp = -1;
		else if (va->ul == vb->ul)
			cmp = 0;
		else
			cmp = 1;
		break;
	}
	return (s->reverse) ? -cmp : cmp;
}