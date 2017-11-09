static void write_filter_rules(int fd)
{
	filter_rule *ent;

	write_sbuf(fd, " <<'#E#'\n");
	for (ent = filter_list.head; ent; ent = ent->next) {
		unsigned int plen;
		char *p = get_rule_prefix(ent, "- ", 0, &plen);
		write_buf(fd, p, plen);
		write_sbuf(fd, ent->pattern);
		if (ent->rflags & FILTRULE_DIRECTORY)
			write_byte(fd, '/');
		write_byte(fd, eol_nulls ? 0 : '\n');
	}
	if (eol_nulls)
		write_sbuf(fd, ";\n");
	write_sbuf(fd, "#E#");
}