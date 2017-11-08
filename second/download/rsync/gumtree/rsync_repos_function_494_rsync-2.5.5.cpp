int poptAddAlias(poptContext con, struct poptAlias newAlias,
		/*@unused@*/ int flags)
{
    int aliasNum = con->numAliases++;
    struct poptAlias * alias;

    /* SunOS won't realloc(NULL, ...) */
    if (!con->aliases)
	con->aliases = malloc(sizeof(newAlias) * con->numAliases);
    else
	con->aliases = realloc(con->aliases,
			       sizeof(newAlias) * con->numAliases);
    alias = con->aliases + aliasNum;

    alias->longName = (newAlias.longName)
	? strcpy(malloc(strlen(newAlias.longName) + 1), newAlias.longName)
	: NULL;
    alias->shortName = newAlias.shortName;
    alias->argc = newAlias.argc;
    alias->argv = newAlias.argv;

    return 0;
}