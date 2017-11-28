void
nsError(int nserror, char *service)
{
    switch (nserror) {
    case HOST_NOT_FOUND:
        error((char *) "%s| %s: ERROR: res_search: Unknown service record: %s\n", LogTime(), PROGRAM, service);
        break;
    case NO_DATA:
        error((char *) "%s| %s: ERROR: res_search: No SRV record for %s\n", LogTime(), PROGRAM, service);
        break;
    case TRY_AGAIN:
        error((char *) "%s| %s: ERROR: res_search: No response for SRV query\n", LogTime(), PROGRAM);
        break;
    default:
        error((char *) "%s| %s: ERROR: res_search: Unexpected error: %s\n", LogTime(), PROGRAM, strerror(nserror));
    }
}