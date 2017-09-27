            continue;
        }
        /* ignore late headers in early calls */
        else if (early && (envar != condition_early)) {
            continue;
        }
        /* Have any conditional envar-controlled Header processing to do? */
        else if (envar && !early) {
            if (*envar != '!') {
                if (apr_table_get(r->subprocess_env, envar) == NULL)
                    continue;
            }
