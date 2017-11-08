static void head_atom_parser(struct used_atom *atom, const char *arg)
{
	unsigned char unused[GIT_SHA1_RAWSZ];

	atom->u.head = resolve_refdup("HEAD", RESOLVE_REF_READING, unused, NULL);
}