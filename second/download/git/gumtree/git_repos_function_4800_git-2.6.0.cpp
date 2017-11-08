static int get_mail_commit_sha1(unsigned char *commit_id, const char *mail)
{
	struct strbuf sb = STRBUF_INIT;
	FILE *fp = xfopen(mail, "r");
	const char *x;

	if (strbuf_getline(&sb, fp, '\n'))
		return -1;

	if (!skip_prefix(sb.buf, "From ", &x))
		return -1;

	if (get_sha1_hex(x, commit_id) < 0)
		return -1;

	strbuf_release(&sb);
	fclose(fp);
	return 0;
}