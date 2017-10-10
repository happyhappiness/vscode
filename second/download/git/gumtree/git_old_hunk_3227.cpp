		/*
		 * If the atom name has a colon, strip it and everything after
		 * it off - it specifies the format for this entry, and
		 * shouldn't be used for checking against the valid_atom
		 * table.
		 */
		const char *formatp = strchr(sp, ':');
		if (!formatp || ep < formatp)
			formatp = ep;
		if (len == formatp - sp && !memcmp(valid_atom[i].name, sp, len))
			break;
	}

	if (ARRAY_SIZE(valid_atom) <= i)
		die("unknown field name: %.*s", (int)(ep-atom), atom);

	/* Add it in, including the deref prefix */
	at = used_atom_cnt;
	used_atom_cnt++;
	REALLOC_ARRAY(used_atom, used_atom_cnt);
	REALLOC_ARRAY(used_atom_type, used_atom_cnt);
	used_atom[at] = xmemdupz(atom, ep - atom);
	used_atom_type[at] = valid_atom[i].cmp_type;
	if (*atom == '*')
		need_tagged = 1;
	if (!strcmp(used_atom[at], "symref"))
		need_symref = 1;
	return at;
}

static void quote_formatting(struct strbuf *s, const char *str, int quote_style)
{
