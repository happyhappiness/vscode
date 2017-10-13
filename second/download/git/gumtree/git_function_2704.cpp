static void subject_atom_parser(struct used_atom *atom, const char *arg)
{
	if (arg)
		die(_("%%(subject) does not take arguments"));
	atom->u.contents.option = C_SUB;
}