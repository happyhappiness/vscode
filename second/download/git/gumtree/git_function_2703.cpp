static void body_atom_parser(struct used_atom *atom, const char *arg)
{
	if (arg)
		die(_("%%(body) does not take arguments"));
	atom->u.contents.option = C_BODY_DEP;
}