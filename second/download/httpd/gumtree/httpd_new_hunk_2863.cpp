            continue;
        }

        rc = rewritemap_program_child(p, map->argv[0], map->argv,
                                      &fpout, &fpin);
        if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s, APLOGNO(00654)
                         "mod_rewrite: could not start RewriteMap "
                         "program %s", map->checkfile);
            return rc;
        }
        map->fpin  = fpin;
        map->fpout = fpout;
