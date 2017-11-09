static void refname_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
{
	refname_atom_parser_internal(&atom->u.refname, arg, atom->name);
}