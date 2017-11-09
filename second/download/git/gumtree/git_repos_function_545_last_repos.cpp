static int parse_ref_filter_atom(const struct ref_format *format,
				 const char *atom, const char *ep)
{
	const char *sp;
	const char *arg;
	int i, at, atom_len;

	sp = atom;
	if (*sp == '*' && sp < ep)
		sp++; /* deref */
	if (ep <= sp)
		die(_("malformed field name: %.*s"), (int)(ep-atom), atom);

	/* Do we have the atom already used elsewhere? */
	for (i = 0; i < used_atom_cnt; i++) {
		int len = strlen(used_atom[i].name);
		if (len == ep - atom && !memcmp(used_atom[i].name, atom, len))
			return i;
	}

	/*
	 * If the atom name has a colon, strip it and everything after
	 * it off - it specifies the format for this entry, and
	 * shouldn't be used for checking against the valid_atom
	 * table.
	 */
	arg = memchr(sp, ':', ep - sp);
	atom_len = (arg ? arg : ep) - sp;

	/* Is the atom a valid one? */
	for (i = 0; i < ARRAY_SIZE(valid_atom); i++) {
		int len = strlen(valid_atom[i].name);
		if (len == atom_len && !memcmp(valid_atom[i].name, sp, len))
			break;
	}

	if (ARRAY_SIZE(valid_atom) <= i)
		die(_("unknown field name: %.*s"), (int)(ep-atom), atom);

	/* Add it in, including the deref prefix */
	at = used_atom_cnt;
	used_atom_cnt++;
	REALLOC_ARRAY(used_atom, used_atom_cnt);
	used_atom[at].name = xmemdupz(atom, ep - atom);
	used_atom[at].type = valid_atom[i].cmp_type;
	if (arg)
		arg = used_atom[at].name + (arg - atom) + 1;
	memset(&used_atom[at].u, 0, sizeof(used_atom[at].u));
	if (valid_atom[i].parser)
		valid_atom[i].parser(format, &used_atom[at], arg);
	if (*atom == '*')
		need_tagged = 1;
	if (!strcmp(valid_atom[i].name, "symref"))
		need_symref = 1;
	return at;
}