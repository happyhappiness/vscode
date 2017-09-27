        apr_pool_destroy(ptemp);
        apr_pool_lock(pconf, 1);

        ap_run_optional_fn_retrieve();

        ap_main_state = AP_SQ_MS_RUN_MPM;
        rc = ap_run_mpm(pconf, plog, ap_server_conf);

        apr_pool_lock(pconf, 0);

    } while (rc == OK);

    if (rc == DONE) {
        rc = OK;
    }
    else if (rc != OK) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, NULL, APLOGNO(02818)
                     "MPM run failed, exiting");
    }
    destroy_and_exit_process(process, rc);

    /* NOTREACHED */
    return !OK;
}

#ifdef AP_USING_AUTOCONF
/* This ugly little hack pulls any function referenced in exports.c into
 * the web server.  exports.c is generated during the build, and it
 * has all of the APR functions specified by the apr/apr.exports and
