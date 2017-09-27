            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "mod_rewrite: could not init rewrite_mapr_lock_acquire"
                         " in child");
        }
    }

    /* create the lookup cache */
    if (!init_cache(p)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "mod_rewrite: could not init map cache in child");
    }
}
