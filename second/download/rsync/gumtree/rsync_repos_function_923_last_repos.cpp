poptContext poptFreeContext(poptContext con)
{
    poptItem item;
    int i;

    if (con == NULL) return con;
    poptResetContext(con);
    con->os->argb = _free(con->os->argb);

    if (con->aliases != NULL)
    for (i = 0; i < con->numAliases; i++) {
	item = con->aliases + i;
	/*@-modobserver -observertrans -dependenttrans@*/
	item->option.longName = _free(item->option.longName);
	item->option.descrip = _free(item->option.descrip);
	item->option.argDescrip = _free(item->option.argDescrip);
	/*@=modobserver =observertrans =dependenttrans@*/
	item->argv = _free(item->argv);
    }
    con->aliases = _free(con->aliases);

    if (con->execs != NULL)
    for (i = 0; i < con->numExecs; i++) {
	item = con->execs + i;
	/*@-modobserver -observertrans -dependenttrans@*/
	item->option.longName = _free(item->option.longName);
	item->option.descrip = _free(item->option.descrip);
	item->option.argDescrip = _free(item->option.argDescrip);
	/*@=modobserver =observertrans =dependenttrans@*/
	item->argv = _free(item->argv);
    }
    con->execs = _free(con->execs);

    con->leftovers = _free(con->leftovers);
    con->finalArgv = _free(con->finalArgv);
    con->appName = _free(con->appName);
    con->otherHelp = _free(con->otherHelp);
    con->execPath = _free(con->execPath);
    con->arg_strip = PBM_FREE(con->arg_strip);
    
    con = _free(con);
    return con;
}