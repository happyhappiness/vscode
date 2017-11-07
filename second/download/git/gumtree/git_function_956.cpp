static int parse_mode_line(const char *line, int linenr, unsigned int *mode)
{
	char *end;
	*mode = strtoul(line, &end, 8);
	if (end == line || !isspace(*end))
		return error(_("invalid mode on line %d: %s"), linenr, line);
	return 0;
}