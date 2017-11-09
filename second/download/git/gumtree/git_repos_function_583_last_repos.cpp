static const char *get_symref(struct used_atom *atom, struct ref_array_item *ref)
{
	if (!ref->symref)
		return "";
	else
		return show_ref(&atom->u.refname, ref->symref);
}