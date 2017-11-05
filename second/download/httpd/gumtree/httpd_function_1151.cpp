static DBPROCESS *freetds_open(apr_pool_t *pool, const char *params,
                               const char **error)
{
    char *server = NULL;
    DBPROCESS *process;
    LOGINREC *login;
    static const char *delims = " \r\n\t;|,";
    char *ptr;
    char *key;
    char *value;
    int vlen;
    int klen;
    char *buf;
    char *databaseName = NULL;

    /* FIXME - this uses malloc */
    /* FIXME - pass error message back to the caller in case of failure */
    login = dblogin();
    if (login == NULL) {
        return NULL;
    }
    /* now set login properties */
    for (ptr = strchr(params, '='); ptr; ptr = strchr(ptr, '=')) {
        /* don't dereference memory that may not belong to us */
        if (ptr == params) {
            ++ptr;
            continue;
        }
        for (key = ptr-1; apr_isspace(*key); --key);
        klen = 0;
        while (apr_isalpha(*key)) {
            --key;
            ++klen;
        }
        ++key;
        for (value = ptr+1; apr_isspace(*value); ++value);

        vlen = strcspn(value, delims);
        buf = apr_pstrndup(pool, value, vlen);        /* NULL-terminated copy */

        if (!strncasecmp(key, "username", klen)) {
            DBSETLUSER(login, buf);
        }
        else if (!strncasecmp(key, "password", klen)) {
            DBSETLPWD(login, buf);
        }
        else if (!strncasecmp(key, "appname", klen)) {
            DBSETLAPP(login, buf);
        }
        else if (!strncasecmp(key, "dbname", klen)) {
            databaseName = buf;
        }
        else if (!strncasecmp(key, "host", klen)) {
            DBSETLHOST(login, buf);
        }
        else if (!strncasecmp(key, "charset", klen)) {
            DBSETLCHARSET(login, buf);
        }
        else if (!strncasecmp(key, "lang", klen)) {
            DBSETLNATLANG(login, buf);
        }
        else if (!strncasecmp(key, "server", klen)) {
            server = buf;
        }
        else {
            /* unknown param */
        }
        ptr = value+vlen;
    }

    process = dbopen(login, server);

    fprintf(stderr, "databaseName [%s]\n", databaseName);

    if (databaseName != NULL)
    {
        dbuse(process, databaseName);
    }
 
    dbloginfree(login);
    if (process == NULL) {
        return NULL;
    }

    return process;
}