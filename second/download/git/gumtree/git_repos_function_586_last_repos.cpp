static void get_ref_atom_value(struct ref_array_item *ref, int atom, struct atom_value **v)
{
	if (!ref->value) {
		populate_value(ref);
		fill_missing_values(ref->value);
	}
	*v = &ref->value[atom];
}