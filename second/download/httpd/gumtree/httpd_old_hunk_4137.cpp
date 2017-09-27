        apr_pool_destroy(ptemp);
        apr_pool_lock(pconf, 1);

        ap_run_optional_fn_retrieve();

        ap_main_state = AP_SQ_MS_RUN_MPM;
        if (ap_run_mpm(pconf, plog, ap_server_conf) != OK)
            break;

        apr_pool_lock(pconf, 0);
    }

    apr_pool_lock(pconf, 0);
    destroy_and_exit_process(process, 0);

    return 0; /* Termination 'ok' */
}

#ifdef AP_USING_AUTOCONF
/* This ugly little hack pulls any function referenced in exports.c into
 * the web server.  exports.c is generated during the build, and it
 * has all of the APR functions specified by the apr/apr.exports and
