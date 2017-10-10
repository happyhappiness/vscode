		free_array_item(array->items[i]);
	free(array->items);
	array->items = NULL;
	array->nr = array->alloc = 0;
}

/*
 * API for filtering a set of refs. Based on the type of refs the user
 * has requested, we iterate through those refs and apply filters
 * as per the given ref_filter structure and finally store the
 * filtered refs in the ref_array structure.
 */
int filter_refs(struct ref_array *array, struct ref_filter *filter, unsigned int type)
{
	struct ref_filter_cbdata ref_cbdata;

	ref_cbdata.array = array;
	ref_cbdata.filter = filter;

	if (type & (FILTER_REFS_ALL | FILTER_REFS_INCLUDE_BROKEN))
		return for_each_rawref(ref_filter_handler, &ref_cbdata);
	else if (type & FILTER_REFS_ALL)
		return for_each_ref(ref_filter_handler, &ref_cbdata);
	else
		die("filter_refs: invalid type");
	return 0;
}

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

static struct ref_sorting *ref_sorting;
static int compare_refs(const void *a_, const void *b_)
{
