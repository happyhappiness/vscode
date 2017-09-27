        ap_regkey_close(key);
    }
    if (rv != APR_SUCCESS) {
        if (rv == ERROR_FILE_NOT_FOUND) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL,
                         "No ConfigArgs registered for %s, perhaps "
                         "this service is not installed?", 
                         mpm_service_name);
            return APR_SUCCESS;
        }
        else
            return (rv);        
    }

    if (!svc_args || svc_args->nelts == 0) {
        return (APR_SUCCESS);
    }

    /* Now we have the mpm_service_name arg, and the mpm_runservice_nt()
     * call appended the arguments passed by StartService(), so it's  
     * time to _prepend_ the default arguments for the server from 
     * the service's default arguments (all others override them)...
     */
    args->nalloc = args->nelts + svc_args->nelts;
    cmb_data = malloc(args->nalloc * sizeof(const char *));

    /* First three args (argv[0], -f, path) remain first */
    memcpy(cmb_data, args->elts, args->elt_size * fixed_args);
    
    /* Service args follow from service registry array */
    memcpy(cmb_data + fixed_args, svc_args->elts, 
           svc_args->elt_size * svc_args->nelts);
    
    /* Remaining new args follow  */
    memcpy(cmb_data + fixed_args + svc_args->nelts,
           (const char **)args->elts + fixed_args, 
           args->elt_size * (args->nelts - fixed_args));
    
    args->elts = (char *)cmb_data;
    args->nelts = args->nalloc;

    return APR_SUCCESS;
}

