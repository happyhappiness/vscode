static void head_atom_parser(const struct ref_format *format, struct used_atom *atom, const char *arg)
{
	struct object_id unused;

	atom->u.head = resolve_refdup("HEAD", RESOLVE_REF_READING, unused.hash, NULL);
}