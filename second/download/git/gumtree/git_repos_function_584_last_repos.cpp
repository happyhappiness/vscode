static const char *get_refname(struct used_atom *atom, struct ref_array_item *ref)
{
	if (ref->kind & FILTER_REFS_DETACHED_HEAD)
		return get_head_description();
	return show_ref(&atom->u.refname, ref->refname);
}