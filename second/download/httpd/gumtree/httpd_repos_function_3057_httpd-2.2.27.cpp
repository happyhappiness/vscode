static apr_status_t crypto_init(apr_pool_t *pool, const char *params,
        const apu_err_t **result)
{
    SECStatus s;
    const char *dir = NULL;
    const char *keyPrefix = NULL;
    const char *certPrefix = NULL;
    const char *secmod = NULL;
    int noinit = 0;
    PRUint32 flags = 0;

    struct {
        const char *field;
        const char *value;
        int set;
    } fields[] = {
        { "dir", NULL, 0 },
        { "key3", NULL, 0 },
        { "cert7", NULL, 0 },
        { "secmod", NULL, 0 },
        { "noinit", NULL, 0 },
        { NULL, NULL, 0 }
    };
    const char *ptr;
    size_t klen;
    char **elts = NULL;
    char *elt;
    int i = 0, j;
    apr_status_t status;

    if (params) {
        if (APR_SUCCESS != (status = apr_tokenize_to_argv(params, &elts, pool))) {
            return status;
        }
        while ((elt = elts[i])) {
            ptr = strchr(elt, '=');
            if (ptr) {
                for (klen = ptr - elt; klen && apr_isspace(elt[klen - 1]); --klen)
                    ;
                ptr++;
            }
            else {
                for (klen = strlen(elt); klen && apr_isspace(elt[klen - 1]); --klen)
                    ;
            }
            elt[klen] = 0;

            for (j = 0; fields[j].field != NULL; ++j) {
                if (klen && !strcasecmp(fields[j].field, elt)) {
                    fields[j].set = 1;
                    if (ptr) {
                        fields[j].value = ptr;
                    }
                    break;
                }
            }

            i++;
        }
        dir = fields[0].value;
        keyPrefix = fields[1].value;
        certPrefix = fields[2].value;
        secmod = fields[3].value;
        noinit = fields[4].set;
    }

    /* if we've been asked to bypass, do so here */
    if (noinit) {
        return APR_SUCCESS;
    }

    /* sanity check - we can only initialise NSS once */
    if (NSS_IsInitialized()) {
        return APR_EREINIT;
    }

    apr_pool_cleanup_register(pool, pool, crypto_shutdown_helper,
            apr_pool_cleanup_null);

    if (keyPrefix || certPrefix || secmod) {
        s = NSS_Initialize(dir, certPrefix, keyPrefix, secmod, flags);
    }
    else if (dir) {
        s = NSS_InitReadWrite(dir);
    }
    else {
        s = NSS_NoDB_Init(NULL);
    }
    if (s != SECSuccess) {
        if (result) {
            apu_err_t *err = apr_pcalloc(pool, sizeof(apu_err_t));
            err->rc = PR_GetError();
            err->msg = PR_ErrorToName(s);
            err->reason = "Error during 'nss' initialisation";
            *result = err;
        }
        return APR_ECRYPT;
    }

    return APR_SUCCESS;

}