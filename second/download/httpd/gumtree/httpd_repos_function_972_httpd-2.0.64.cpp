static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
                                  const char *a2)
{
    rewrite_server_conf *sconf;
    rewritemap_entry *newmap;
    apr_finfo_t st;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    newmap = apr_array_push(sconf->rewritemaps);

    newmap->name = a1;
    newmap->func = NULL;
    if (strncmp(a2, "txt:", 4) == 0) {
        newmap->type      = MAPTYPE_TXT;
        newmap->datafile  = a2+4;
        newmap->checkfile = a2+4;
        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
                                         (void *)cmd->server, a1);
    }
    else if (strncmp(a2, "rnd:", 4) == 0) {
        newmap->type      = MAPTYPE_RND;
        newmap->datafile  = a2+4;
        newmap->checkfile = a2+4;
        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
                                         (void *)cmd->server, a1);
    }
    else if (strncmp(a2, "dbm", 3) == 0) {
        const char *ignored_fname;
        int bad = 0;
        apr_status_t rv;

        newmap->type = MAPTYPE_DBM;
        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
                                         (void *)cmd->server, a1);

        if (a2[3] == ':') {
            newmap->dbmtype    = "default";
            newmap->datafile   = a2+4;
        }
        else if (a2[3] == '=') {
            const char *colon = ap_strchr_c(a2 + 4, ':');

            if (colon) {
                newmap->dbmtype = apr_pstrndup(cmd->pool, a2 + 4,
                                               colon - (a2 + 3) - 1);
                newmap->datafile = colon + 1;
            }
            else {
                ++bad;
            }
        }
        else {
            ++bad;
        }

        if (bad) {
            return apr_pstrcat(cmd->pool, "RewriteMap: bad map:",
                               a2, NULL);
        }

        rv = apr_dbm_get_usednames_ex(cmd->pool, newmap->dbmtype,
                                      newmap->datafile, &newmap->checkfile,
                                      &ignored_fname);
        if (rv != APR_SUCCESS) {
            return apr_pstrcat(cmd->pool, "RewriteMap: dbm type ",
                               newmap->dbmtype, " is invalid", NULL);
        }
    }
    else if (strncmp(a2, "prg:", 4) == 0) {
        newmap->type      = MAPTYPE_PRG;
        apr_tokenize_to_argv(a2 + 4, &newmap->argv, cmd->pool);
        newmap->datafile  = NULL;
        newmap->checkfile = newmap->argv[0];
        newmap->cachename = NULL;

    }
    else if (strncmp(a2, "int:", 4) == 0) {
        newmap->type      = MAPTYPE_INT;
        newmap->datafile  = NULL;
        newmap->checkfile = NULL;
        newmap->cachename = NULL;
        newmap->func      = (char *(*)(request_rec *,char *))
                            apr_hash_get(mapfunc_hash, a2+4, strlen(a2+4));
        if ((sconf->state == ENGINE_ENABLED) && (newmap->func == NULL)) {
            return apr_pstrcat(cmd->pool, "RewriteMap: internal map not found:",
                               a2+4, NULL);
        }
    }
    else {
        newmap->type      = MAPTYPE_TXT;
        newmap->datafile  = a2;
        newmap->checkfile = a2;
        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
                                         (void *)cmd->server, a1);
    }
    newmap->fpin  = NULL;
    newmap->fpout = NULL;

    if (newmap->checkfile && (sconf->state == ENGINE_ENABLED)
        && (apr_stat(&st, newmap->checkfile, APR_FINFO_MIN,
                     cmd->pool) != APR_SUCCESS)) {
        return apr_pstrcat(cmd->pool,
                           "RewriteMap: file for map ", newmap->name,
                           " not found:", newmap->checkfile, NULL);
    }

    return NULL;
}