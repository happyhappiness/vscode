static void NORETURN unsupported_magic(const char *pattern,
				       unsigned magic,
				       unsigned short_magic)
{
	struct strbuf sb = STRBUF_INIT;
	int i, n;
	for (n = i = 0; i < ARRAY_SIZE(pathspec_magic); i++) {
		const struct pathspec_magic *m = pathspec_magic + i;
		if (!(magic & m->bit))
			continue;
		if (sb.len)
			strbuf_addch(&sb, ' ');
		if (short_magic & m->bit)
			strbuf_addf(&sb, "'%c'", m->mnemonic);
		else
			strbuf_addf(&sb, "'%s'", m->name);
		n++;
	}
	/*
	 * We may want to substitute "this command" with a command
	 * name. E.g. when add--interactive dies when running
	 * "checkout -p"
	 */
	die(_("%s: pathspec magic not supported by this command: %s"),
	    pattern, sb.buf);
}