static void copy_gecos(const struct passwd *w, struct strbuf *name)
{
	char *src;

	/* Traditionally GECOS field had office phone numbers etc, separated
	 * with commas.  Also & stands for capitalized form of the login name.
	 */

	for (src = get_gecos(w); *src && *src != ','; src++) {
		int ch = *src;
		if (ch != '&')
			strbuf_addch(name, ch);
		else {
			/* Sorry, Mr. McDonald... */
			strbuf_addch(name, toupper(*w->pw_name));
			strbuf_addstr(name, w->pw_name + 1);
		}
	}
}