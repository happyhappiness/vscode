void
AddServer(char *ParamPDC, char *ParamBDC, char *ParamDomain)
{
    if (Serversqueried == MAXSERVERS) {
        syslog(LOG_ERR, "AddServer: Ignoring '%s' server line; "
               "too many servers.", ParamPDC);
        return;
    }
    if (gethostbyname(ParamPDC) == NULL) {
        syslog(LOG_ERR, "AddServer: Ignoring host '%s'. "
               "Cannot resolve its address.", ParamPDC);
        return;
    }
    if (gethostbyname(ParamBDC) == NULL) {
        syslog(LOG_USER | LOG_ERR, "AddServer: Ignoring host '%s'. "
               "Cannot resolve its address.", ParamBDC);
        return;
    }
    /* NOTE: ServerArray is zeroed in OpenConfigFile() */
    assert(Serversqueried < MAXSERVERS);
    strncpy(ServerArray[Serversqueried].pdc, ParamPDC, NTHOSTLEN - 1);
    strncpy(ServerArray[Serversqueried].bdc, ParamBDC, NTHOSTLEN - 1);
    strncpy(ServerArray[Serversqueried].domain, ParamDomain, NTHOSTLEN - 1);
    Serversqueried++;
}