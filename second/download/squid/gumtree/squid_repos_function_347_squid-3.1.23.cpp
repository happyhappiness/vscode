static void
ProcessLine(char *Linebuf)
{
    char *Directive;
    char *Param1;
    char *Param2;
    char *Param3;

    /* Ignore empty lines */
    if (strlen(Linebuf) == 0)
        return;

    /* Break up on whitespaces */
    if ((Directive = strtok(Linebuf, " \t\n")) == NULL)
        return;

    /* Check for a comment line. If found, stop . */
    if (Directive[0] == '#')
        return;

    /* Check for server line. Check for 3 parameters. */
    if (strcasecmp(Directive, "server") == 0) {
        Param1 = strtok(NULL, " \t\n");
        if (NULL == Param1) {
            syslog(LOG_ERR, "ProcessLine: 'server' missing PDC parameter.");
            return;
        }
        Param2 = strtok(NULL, " \t\n");
        if (NULL == Param2) {
            syslog(LOG_ERR, "ProcessLine: 'server' missing BDC parameter.");
            return;
        }
        Param3 = strtok(NULL, " \t\n");
        if (NULL == Param3) {
            syslog(LOG_ERR, "ProcessLine: 'server' missing domain parameter.");
            return;
        }
        AddServer(Param1, Param2, Param3);
        return;
    }
    /* Check for denyusers line */
    if (strcasecmp(Directive, "denyusers") == 0) {
        Param1 = strtok(NULL, " \t\n");

        if (NULL == Param1) {
            syslog(LOG_ERR, "ProcessLine: A 'denyusers' line needs a filename parameter.");
            return;
        }
        memset(Denyuserpath, '\0', MAXPATHLEN);
        strncpy(Denyuserpath, Param1, MAXPATHLEN - 1);
        return;
    }
    /* Check for allowusers line */
    if (strcasecmp(Directive, "allowusers") == 0) {
        Param1 = strtok(NULL, " \t\n");

        if (NULL == Param1) {
            syslog(LOG_ERR, "ProcessLine: An 'allowusers' line needs a filename parameter.");
            return;
        }
        memset(Allowuserpath, '\0', MAXPATHLEN);
        strncpy(Allowuserpath, Param1, MAXPATHLEN - 1);
        return;
    }
    /* Reports error for unknown line */
    syslog(LOG_ERR, "ProcessLine: Ignoring '%s' line.", Directive);
}