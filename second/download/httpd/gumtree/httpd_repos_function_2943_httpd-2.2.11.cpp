static apr_dbd_t *dbd_mysql_open(apr_pool_t *pool, const char *params,
                                 const char **error)
{
    static const char *const delims = " \r\n\t;|,";
    const char *ptr;
    int i;
    const char *key;
    size_t klen;
    const char *value;
    size_t vlen;
#if MYSQL_VERSION_ID >= 50013
    my_bool do_reconnect = 1;
#endif
    MYSQL *real_conn;
    unsigned long flags = 0;
    
    struct {
        const char *field;
        const char *value;
    } fields[] = {
        {"host", NULL},
        {"user", NULL},
        {"pass", NULL},
        {"dbname", NULL},
        {"port", NULL},
        {"sock", NULL},
        {"flags", NULL},
        {"fldsz", NULL},
        {"group", NULL},
        {"reconnect", NULL},
        {NULL, NULL}
    };
    unsigned int port = 0;
    apr_dbd_t *sql = apr_pcalloc(pool, sizeof(apr_dbd_t));
    sql->fldsz = FIELDSIZE;
    sql->conn = mysql_init(sql->conn);
    if ( sql->conn == NULL ) {
        return NULL;
    }
    for (ptr = strchr(params, '='); ptr; ptr = strchr(ptr, '=')) {
        /* don't dereference memory that may not belong to us */
        if (ptr == params) {
            ++ptr;
            continue;
        }
        for (key = ptr-1; apr_isspace(*key); --key);
        klen = 0;
        while (apr_isalpha(*key)) {
            /* don't parse backwards off the start of the string */
            if (key == params) {
                --key;
                ++klen;
                break;
            }
            --key;
            ++klen;
        }
        ++key;
        for (value = ptr+1; apr_isspace(*value); ++value);
        vlen = strcspn(value, delims);
        for (i = 0; fields[i].field != NULL; i++) {
            if (!strncasecmp(fields[i].field, key, klen)) {
                fields[i].value = apr_pstrndup(pool, value, vlen);
                break;
            }
        }
        ptr = value+vlen;
    }
    if (fields[4].value != NULL) {
        port = atoi(fields[4].value);
    }
    if (fields[6].value != NULL &&
        !strcmp(fields[6].value, "CLIENT_FOUND_ROWS")) {
        flags |= CLIENT_FOUND_ROWS; /* only option we know */
    }
    if (fields[7].value != NULL) {
        sql->fldsz = atol(fields[7].value);
    }
    if (fields[8].value != NULL) {
         mysql_options(sql->conn, MYSQL_READ_DEFAULT_GROUP, fields[8].value);
    }
#if MYSQL_VERSION_ID >= 50013
    if (fields[9].value != NULL) {
         do_reconnect = atoi(fields[9].value) ? 1 : 0;
    }
#endif

#if MYSQL_VERSION_ID >= 50013
    /* the MySQL manual says this should be BEFORE mysql_real_connect */
    mysql_options(sql->conn, MYSQL_OPT_RECONNECT, &do_reconnect);
#endif
    
    real_conn = mysql_real_connect(sql->conn, fields[0].value,
                                   fields[1].value, fields[2].value,
                                   fields[3].value, port,
                                   fields[5].value, flags);

    if(real_conn == NULL) {
        if (error) {
            *error = apr_pstrdup(pool, mysql_error(sql->conn));
        }
        mysql_close(sql->conn);
        return NULL;
    }

#if MYSQL_VERSION_ID >= 50013
    /* Some say this should be AFTER mysql_real_connect */
    mysql_options(sql->conn, MYSQL_OPT_RECONNECT, &do_reconnect);
#endif

    return sql;
}