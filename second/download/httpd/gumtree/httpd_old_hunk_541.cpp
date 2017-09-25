        }
    }
    ap_cfg_closefile(f);
    return NULL;
}

static apr_table_t *groups_for_user(apr_pool_t *p, char *user, char *grpfile)
{
    ap_configfile_t *f;
    apr_table_t *grps = apr_table_make(p, 15);
    apr_pool_t *sp;
    char l[MAX_STRING_LEN];
    const char *group_name, *ll, *w;
    apr_status_t status;

    if ((status = ap_pcfg_openfile(&f, p, grpfile)) != APR_SUCCESS) {
/*add?  aplog_error(APLOG_MARK, APLOG_ERR, NULL,
                    "Could not open group file: %s", grpfile);*/
        return NULL;
    }

    apr_pool_create(&sp, p);

    while (!(ap_cfg_getline(l, MAX_STRING_LEN, f))) {
