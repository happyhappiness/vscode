static apr_dbd_t *dbd_oracle_open(apr_pool_t *pool, const char *params,
                                  const char **error)
{
    apr_dbd_t *ret = apr_pcalloc(pool, sizeof(apr_dbd_t));
    int errorcode;

    char *BLANK = "";
    struct {
        const char *field;
        char *value;
    } fields[] = {
        {"user", BLANK},
        {"pass", BLANK},
        {"dbname", BLANK},
        {"server", BLANK},
        {NULL, NULL}
    };
    int i;
    const char *ptr;
    const char *key;
    size_t klen;
    const char *value;
    size_t vlen;
    static const char *const delims = " \r\n\t;|,";

    ret->pool = pool;
    ret->long_size = DEFAULT_LONG_SIZE;

    /* snitch parsing from the MySQL driver */
    for (ptr = strchr(params, '='); ptr; ptr = strchr(ptr, '=')) {
        /* don't dereference memory that may not belong to us */
        if (ptr == params) {
            ++ptr;
            continue;
        }
        for (key = ptr-1; apr_isspace(*key); --key);
        klen = 0;
        while (apr_isalpha(*key)) {
            if (key == params) {
                /* Don't parse off the front of the params */
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
        for (i=0; fields[i].field != NULL; ++i) {
            if (!strncasecmp(fields[i].field, key, klen)) {
                fields[i].value = apr_pstrndup(pool, value, vlen);
                break;
            }
        }
        ptr = value+vlen;
    }

    ret->status = OCIHandleAlloc(dbd_oracle_env, (dvoid**)&ret->err,
                                 OCI_HTYPE_ERROR, 0, NULL);
    switch (ret->status) {
    default:
#ifdef DEBUG
        printf("ret->status is %d\n", ret->status);
        break;
#else
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }

    ret->status = OCIHandleAlloc(dbd_oracle_env, (dvoid**)&ret->svr,
                                 OCI_HTYPE_SERVER, 0, NULL);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (alloc svr): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }

    ret->status = OCIHandleAlloc(dbd_oracle_env, (dvoid**)&ret->svc,
                                 OCI_HTYPE_SVCCTX, 0, NULL);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (alloc svc): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }

/* All the examples use the #else */
#if CAN_DO_LOGIN
    ret->status = OCILogon(dbd_oracle_env, ret->err, &ret->svc, fields[0].value,
                     strlen(fields[0].value), fields[1].value,
                     strlen(fields[1].value), fields[2].value,
                     strlen(fields[2].value));
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR: %s\n", ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }
#else
    ret->status = OCIServerAttach(ret->svr, ret->err, (text*) fields[3].value,
                                  strlen(fields[3].value), OCI_DEFAULT);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (server attach): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }
    ret->status = OCIAttrSet(ret->svc, OCI_HTYPE_SVCCTX, ret->svr, 0,
                        OCI_ATTR_SERVER, ret->err);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (attr set): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }
    ret->status = OCIHandleAlloc(dbd_oracle_env, (dvoid**)&ret->auth,
                            OCI_HTYPE_SESSION, 0, NULL);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (alloc auth): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }
    ret->status = OCIAttrSet(ret->auth, OCI_HTYPE_SESSION, fields[0].value,
                        strlen(fields[0].value), OCI_ATTR_USERNAME, ret->err);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (attr username): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }
    ret->status = OCIAttrSet(ret->auth, OCI_HTYPE_SESSION, fields[1].value,
                        strlen(fields[1].value), OCI_ATTR_PASSWORD, ret->err);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (attr password): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }
    ret->status = OCISessionBegin(ret->svc, ret->err, ret->auth,
                             OCI_CRED_RDBMS, OCI_DEFAULT);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (session begin): %s\n", ret->status, ret->buf);
        break;
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
    case OCI_SUCCESS:
        break;
    }
    ret->status = OCIAttrSet(ret->svc, OCI_HTYPE_SVCCTX, ret->auth, 0,
                        OCI_ATTR_SESSION, ret->err);
    switch (ret->status) {
    default:
#ifdef DEBUG
        OCIErrorGet(ret->err, 1, NULL, &errorcode, ret->buf,
                    sizeof(ret->buf), OCI_HTYPE_ERROR);
        printf("OPEN ERROR %d (attr session): %s\n", ret->status, ret->buf);
#else
        if (error) {
            *error = apr_pcalloc(pool, ERR_BUF_SIZE);
            OCIErrorGet(ret->err, 1, NULL, &errorcode, (unsigned char*)(*error),
                        ERR_BUF_SIZE, OCI_HTYPE_ERROR);
        }
        return NULL;
#endif
        break;
    case OCI_SUCCESS:
        break;
    }
#endif

    if(dbd_oracle_prepare(pool, ret, CHECK_CONN_QUERY, NULL, 0, 0, NULL,
                          &ret->check_conn_stmt) != 0) {
        return NULL;
    }

    return ret;
}