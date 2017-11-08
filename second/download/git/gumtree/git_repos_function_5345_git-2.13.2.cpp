static int get_mail_commit_oid(struct object_id *commit_id, const char *mail)
{
	struct strbuf sb = STRBUF_INIT;
	FILE *fp = xfopen(mail, "r");
	const char *x;
	int ret = 0;

	if (strbuf_getline_lf(&sb, fp) ||
	    !skip_prefix(sb.buf, "From ", &x) ||
	    get_oid_hex(x, commit_id) < 0)
		ret = -1;

	strbuf_release(&sb);
	fclose(fp);
	return ret;
}