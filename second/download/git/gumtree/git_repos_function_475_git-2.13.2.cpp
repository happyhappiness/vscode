static void refname_atom_parser(struct used_atom *atom, const char *arg)
{
	return refname_atom_parser_internal(&atom->u.refname, arg, atom->name);
}