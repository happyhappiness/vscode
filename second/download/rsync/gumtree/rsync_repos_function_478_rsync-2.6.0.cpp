static void configLine(poptContext con, char * line)
	/*@modifies con @*/
{
    /*@-type@*/
    int nameLength = strlen(con->appName);
    /*@=type@*/
    const char * entryType;
    const char * opt;
    poptItem item = (poptItem) alloca(sizeof(*item));
    int i, j;
    
    memset(item, 0, sizeof(*item));

    /*@-type@*/
    if (strncmp(line, con->appName, nameLength)) return;
    /*@=type@*/

    line += nameLength;
    if (*line == '\0' || !isspace(*line)) return;

    while (*line != '\0' && isspace(*line)) line++;
    entryType = line;
    while (*line == '\0' || !isspace(*line)) line++;
    *line++ = '\0';

    while (*line != '\0' && isspace(*line)) line++;
    if (*line == '\0') return;
    opt = line;
    while (*line == '\0' || !isspace(*line)) line++;
    *line++ = '\0';

    while (*line != '\0' && isspace(*line)) line++;
    if (*line == '\0') return;

    /*@-temptrans@*/ /* FIX: line alias is saved */
    if (opt[0] == '-' && opt[1] == '-')
	item->option.longName = opt + 2;
    else if (opt[0] == '-' && opt[2] == '\0')
	item->option.shortName = opt[1];
    /*@=temptrans@*/

    if (poptParseArgvString(line, &item->argc, &item->argv)) return;

    /*@-modobserver@*/
    item->option.argInfo = POPT_ARGFLAG_DOC_HIDDEN;
    for (i = 0, j = 0; i < item->argc; i++, j++) {
	const char * f;
	if (!strncmp(item->argv[i], "--POPTdesc=", sizeof("--POPTdesc=")-1)) {
	    f = item->argv[i] + sizeof("--POPTdesc=");
	    if (f[0] == '$' && f[1] == '"') f++;
	    item->option.descrip = f;
	    item->option.argInfo &= ~POPT_ARGFLAG_DOC_HIDDEN;
	    j--;
	} else
	if (!strncmp(item->argv[i], "--POPTargs=", sizeof("--POPTargs=")-1)) {
	    f = item->argv[i] + sizeof("--POPTargs=");
	    if (f[0] == '$' && f[1] == '"') f++;
	    item->option.argDescrip = f;
	    item->option.argInfo &= ~POPT_ARGFLAG_DOC_HIDDEN;
	    item->option.argInfo |= POPT_ARG_STRING;
	    j--;
	} else
	if (j != i)
	    item->argv[j] = item->argv[i];
    }
    if (j != i) {
	item->argv[j] = NULL;
	item->argc = j;
    }
    /*@=modobserver@*/
	
    /*@-nullstate@*/ /* FIX: item->argv[] may be NULL */
    if (!strcmp(entryType, "alias"))
	(void) poptAddItem(con, item, 0);
    else if (!strcmp(entryType, "exec"))
	(void) poptAddItem(con, item, 1);
    /*@=nullstate@*/
}