static int credential_do(struct credential *c, const char *helper,
			 const char *operation)
{
	struct strbuf cmd = STRBUF_INIT;
	int r;

	if (helper[0] == '!')
		strbuf_addstr(&cmd, helper + 1);
	else if (is_absolute_path(helper))
		strbuf_addstr(&cmd, helper);
	else
		strbuf_addf(&cmd, "git credential-%s", helper);

	strbuf_addf(&cmd, " %s", operation);
	r = run_credential_helper(c, cmd.buf, !strcmp(operation, "get"));

	strbuf_release(&cmd);
	return r;
}