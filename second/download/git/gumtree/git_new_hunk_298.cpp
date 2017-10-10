		return -1;

	die_errno(_("could not read '%s'"), am_path(state, file));
}

/**
 * Take a series of KEY='VALUE' lines where VALUE part is
 * sq-quoted, and append <KEY, VALUE> at the end of the string list
 */
static int parse_key_value_squoted(char *buf, struct string_list *list)
{
	while (*buf) {
		struct string_list_item *item;
		char *np;
		char *cp = strchr(buf, '=');
		if (!cp)
			return -1;
		np = strchrnul(cp, '\n');
		*cp++ = '\0';
		item = string_list_append(list, buf);

		buf = np + (*np == '\n');
		*np = '\0';
		cp = sq_dequote(cp);
		if (!cp)
			return -1;
		item->util = xstrdup(cp);
	}
	return 0;
}

/**
 * Reads and parses the state directory's "author-script" file, and sets
 * state->author_name, state->author_email and state->author_date accordingly.
 * Returns 0 on success, -1 if the file could not be parsed.
