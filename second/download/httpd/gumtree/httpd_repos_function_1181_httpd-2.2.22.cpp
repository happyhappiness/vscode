static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
                                  const char *a2)
{
    rewrite_server_conf *sconf;
    rewritemap_entry *newmap;
    apr_finfo_t st;
    const char *fname;

    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);

    newmap = apr_palloc(cmd->pool, sizeof(rewritemap_entry));
    newmap->func = NULL;

    if (strncasecmp(a2, "txt:", 4) == 0) {
        if ((fname = ap_server_root_relative(cmd->pool, a2+4)) == NULL) {
            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to txt map: ",
                               a2+4, NULL);
        }

        newmap->type      = MAPTYPE_TXT;
        newmap->datafile  = fname;
        newmap->checkfile = fname;
        newmap->checkfile2= NULL;
        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
                                         (void *)cmd->server, a1);
    }
    else if (strncasecmp(a2, "rnd:", 4) == 0) {
        if ((fname = ap_server_root_relative(cmd->pool, a2+4)) == NULL) {
            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to rnd map: ",
                               a2+4, NULL);
        }

        newmap->type      = MAPTYPE_RND;
        newmap->datafile  = fname;
        newmap->checkfile = fname;
        newmap->checkfile2= NULL;
        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
                                         (void *)cmd->server, a1);
    }
    else if (strncasecmp(a2, "dbm", 3) == 0) {
        apr_status_t rv;

        newmap->type = MAPTYPE_DBM;
        fname = NULL;
        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
                                         (void *)cmd->server, a1);

        if (a2[3] == ':') {
            newmap->dbmtype = "default";
            fname = a2+4;
        }
        else if (a2[3] == '=') {
            const char *colon = ap_strchr_c(a2 + 4, ':');

            if (colon) {
                newmap->dbmtype = apr_pstrndup(cmd->pool, a2 + 4,
                                               colon - (a2 + 3) - 1);
                fname = colon + 1;
            }
        }

        if (!fname) {
            return apr_pstrcat(cmd->pool, "RewriteMap: bad map:",
                               a2, NULL);
        }

        if ((newmap->datafile = ap_server_root_relative(cmd->pool,
                                                        fname)) == NULL) {
            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to dbm map: ",
                               fname, NULL);
        }

        rv = apr_dbm_get_usednames_ex(cmd->pool, newmap->dbmtype,
                                      newmap->datafile, &newmap->checkfile,
                                      &newmap->checkfile2);
        if (rv != APR_SUCCESS) {
            return apr_pstrcat(cmd->pool, "RewriteMap: dbm type ",
                               newmap->dbmtype, " is invalid", NULL);
        }
    }
    else if (strncasecmp(a2, "prg:", 4) == 0) {
        apr_tokenize_to_argv(a2 + 4, &newmap->argv, cmd->pool);

        fname = newmap->argv[0];
        if ((newmap->argv[0] = ap_server_root_relative(cmd->pool,
                                                       fname)) == NULL) {
            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to prg map: ",
                               fname, NULL);
        }

        newmap->type      = MAPTYPE_PRG;
        newmap->datafile  = NULL;
        newmap->checkfile = newmap->argv[0];
        newmap->checkfile2= NULL;
        newmap->cachename = NULL;
    }
    else if (strncasecmp(a2, "int:", 4) == 0) {
        newmap->type      = MAPTYPE_INT;
        newmap->datafile  = NULL;
        newmap->checkfile = NULL;
        newmap->checkfile2= NULL;
        newmap->cachename = NULL;
        newmap->func      = (char *(*)(request_rec *,char *))
                            apr_hash_get(mapfunc_hash, a2+4, strlen(a2+4));
        if (newmap->func == NULL) {
            return apr_pstrcat(cmd->pool, "RewriteMap: internal map not found:",
                               a2+4, NULL);
