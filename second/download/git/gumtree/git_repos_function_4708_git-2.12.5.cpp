static void check_mailmap(struct string_list *mailmap, const char *contact)
{
	const char *name, *mail;
	size_t namelen, maillen;
	struct ident_split ident;

	if (split_ident_line(&ident, contact, strlen(contact)))
		die(_("unable to parse contact: %s"), contact);

	name = ident.name_begin;
	namelen = ident.name_end - ident.name_begin;
	mail = ident.mail_begin;
	maillen = ident.mail_end - ident.mail_begin;

	map_user(mailmap, &mail, &maillen, &name, &namelen);

	if (namelen)
		printf("%.*s ", (int)namelen, name);
	printf("<%.*s>\n", (int)maillen, mail);
}