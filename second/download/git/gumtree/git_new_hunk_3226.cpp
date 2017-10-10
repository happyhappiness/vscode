};

struct atom_value {
	const char *s;
	union {
		struct align align;
	} u;
	void (*handler)(struct atom_value *atomv, struct ref_formatting_state *state);
	unsigned long ul; /* used for sorting when not FIELD_STR */
};

/*
 * Used to parse format string and sort specifiers
 */
int parse_ref_filter_atom(const char *atom, const char *ep)
{
	const char *sp;
	const char *arg;
	int i, at;

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

	/* Is the atom a valid one? */
	for (i = 0; i < ARRAY_SIZE(valid_atom); i++) {
		int len = strlen(valid_atom[i].name);
