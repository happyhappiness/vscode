            continue;
        }
        if (!(map->argv[0]) || !*(map->argv[0]) || map->fpin || map->fpout) {
            continue;
        }

        rc = rewritemap_program_child(p, map->argv[0], map->argv,
                                      &fpout, &fpin);
        if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
                         "mod_rewrite: could not start RewriteMap "
                         "program %s", map->checkfile);
