static int do_sign(struct strbuf *buffer)
{
	return sign_buffer(buffer, buffer, get_signing_key());
}

static const char tag_template[] =
	N_("\nWrite a tag message\n"
	"Lines starting with '%c' will be ignored.\n");

static const char tag_template_nocleanup[] =
	N_("\nWrite a tag message\n"
	"Lines starting with '%c' will be kept; you may remove them"
	" yourself if you want to.\n");

static int git_tag_config(const char *var, const char *value, void *cb)
{
	int status = git_gpg_config(var, value, cb);
	if (status)
		return status;
	if (starts_with(var, "column."))
		return git_column_config(var, value, "tag", &colopts);
	return git_default_config(var, value, cb);
}
