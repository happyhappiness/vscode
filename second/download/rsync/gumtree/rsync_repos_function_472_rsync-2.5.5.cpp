static void configLine(poptContext con, char * line) {
    int nameLength = strlen(con->appName);
    char * opt;
    struct poptAlias alias;
    char * entryType;
    char * longName = NULL;
    char shortName = '\0';
    
    if (strncmp(line, con->appName, nameLength)) return;
    line += nameLength;
    if (!*line || !isspace(*line)) return;
    while (*line && isspace(*line)) line++;
    entryType = line;

    while (!*line || !isspace(*line)) line++;
    *line++ = '\0';
    while (*line && isspace(*line)) line++;
    if (!*line) return;
    opt = line;

    while (!*line || !isspace(*line)) line++;
    *line++ = '\0';
    while (*line && isspace(*line)) line++;
    if (!*line) return;

    if (opt[0] == '-' && opt[1] == '-')
	longName = opt + 2;
    else if (opt[0] == '-' && !opt[2])
	shortName = opt[1];

    if (!strcmp(entryType, "alias")) {
	if (poptParseArgvString(line, &alias.argc, &alias.argv)) return;
	alias.longName = longName, alias.shortName = shortName;
	poptAddAlias(con, alias, 0);
    } else if (!strcmp(entryType, "exec")) {
	con->execs = realloc(con->execs,
				sizeof(*con->execs) * (con->numExecs + 1));
	if (longName)
	    con->execs[con->numExecs].longName = xstrdup(longName);
	else
	    con->execs[con->numExecs].longName = NULL;

	con->execs[con->numExecs].shortName = shortName;
	con->execs[con->numExecs].script = xstrdup(line);
	
	con->numExecs++;
    }
}