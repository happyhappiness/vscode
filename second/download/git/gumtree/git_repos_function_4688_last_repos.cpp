static void NORETURN unsupported_magic(const char *pattern,
				       unsigned magic)
{
	struct strbuf sb = STRBUF_INIT;
	int i;
	for (i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
		const struct pathspec_magic *m = pathspec_magic + i;
		if (!(magic & m->bit))
			continue;
		if (sb.len)
			strbuf_addstr(&sb, ", ");

		if (m->mnemonic)
			strbuf_addf(&sb, _("'%s' (mnemonic: '%c')"),
				    m->name, m->mnemonic);
		else
			strbuf_addf(&sb, "'%s'", m->name);
	}
	/*
	 * We may want to substitute "this command" with a command
	 * name. E.g. when add--interactive dies when running
	 * "checkout -p"
	 */
	die(_("%s: pathspec magic not supported by this command: %s"),
	    pattern, sb.buf);
}