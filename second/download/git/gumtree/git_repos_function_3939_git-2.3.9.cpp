static void exec_man_cmd(const char *cmd, const char *page)
{
	struct strbuf shell_cmd = STRBUF_INIT;
	strbuf_addf(&shell_cmd, "%s %s", cmd, page);
	execl("/bin/sh", "sh", "-c", shell_cmd.buf, (char *)NULL);
	warning(_("failed to exec '%s': %s"), cmd, strerror(errno));
}