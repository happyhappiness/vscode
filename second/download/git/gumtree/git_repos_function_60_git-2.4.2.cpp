static void list_commands_in_dir(struct cmdnames *cmds,
					 const char *path,
					 const char *prefix)
{
	DIR *dir = opendir(path);
	struct dirent *de;
	struct strbuf buf = STRBUF_INIT;
	int len;

	if (!dir)
		return;
	if (!prefix)
		prefix = "git-";

	strbuf_addf(&buf, "%s/", path);
	len = buf.len;

	while ((de = readdir(dir)) != NULL) {
		const char *ent;
		size_t entlen;

		if (!skip_prefix(de->d_name, prefix, &ent))
			continue;

		strbuf_setlen(&buf, len);
		strbuf_addstr(&buf, de->d_name);
		if (!is_executable(buf.buf))
			continue;

		entlen = strlen(ent);
		strip_suffix(ent, ".exe", &entlen);

		add_cmdname(cmds, ent, entlen);
	}
	closedir(dir);
	strbuf_release(&buf);
}