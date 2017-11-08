static int match_atom_name(const char *name, const char *atom_name, const char **val)
{
	const char *body;

	if (!skip_prefix(name, atom_name, &body))
		return 0; /* doesn't even begin with "atom_name" */
	if (!body[0]) {
		*val = NULL; /* %(atom_name) and no customization */
		return 1;
	}
	if (body[0] != ':')
		return 0; /* "atom_namefoo" is not "atom_name" or "atom_name:..." */
	*val = body + 1; /* "atom_name:val" */
	return 1;
}