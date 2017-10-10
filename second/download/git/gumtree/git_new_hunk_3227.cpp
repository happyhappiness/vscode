		/*
		 * If the atom name has a colon, strip it and everything after
		 * it off - it specifies the format for this entry, and
		 * shouldn't be used for checking against the valid_atom
		 * table.
		 */
		arg = memchr(sp, ':', ep - sp);
		if (len == (arg ? arg : ep) - sp &&
		    !memcmp(valid_atom[i].name, sp, len))
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
		valid_atom[i].parser(&used_atom[at], arg);
	if (*atom == '*')
		need_tagged = 1;
	if (!strcmp(used_atom[at].name, "symref"))
		need_symref = 1;
	return at;
}

static void quote_formatting(struct strbuf *s, const char *str, int quote_style)
{
