static int intend_to_amend(void)
{
	unsigned char head[20];
	char *p;

	if (get_sha1("HEAD", head))
		return error(_("cannot read HEAD"));

	p = sha1_to_hex(head);
	return write_message(p, strlen(p), rebase_path_amend(), 1);
}