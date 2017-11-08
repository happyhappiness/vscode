static void get_value(struct refinfo *ref, int atom, struct atom_value **v)
{
	if (!ref->value) {
		populate_value(ref);
		fill_missing_values(ref->value);
	}
	*v = &ref->value[atom];
}