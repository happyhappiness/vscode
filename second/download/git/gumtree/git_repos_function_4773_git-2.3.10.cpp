static const char *clean_message_id(const char *msg_id)
{
	char ch;
	const char *a, *z, *m;

	m = msg_id;
	while ((ch = *m) && (isspace(ch) || (ch == '<')))
		m++;
	a = m;
	z = NULL;
	while ((ch = *m)) {
		if (!isspace(ch) && (ch != '>'))
			z = m;
		m++;
	}
	if (!z)
		die(_("insane in-reply-to: %s"), msg_id);
	if (++z == m)
		return a;
	return xmemdupz(a, z - a);
}