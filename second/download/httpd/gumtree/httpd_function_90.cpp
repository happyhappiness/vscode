static void send_req(int fd, request_rec *r, char *argv0, char **env, int req_type) 
{ 
    int len, r_type = req_type; 
    int i = 0; 
    char *data; 
    module *suexec_mod = ap_find_linked_module("mod_suexec.c");

    data = apr_pstrcat(r->pool, r->filename, "\n", argv0, "\n", r->uri, "\n", 
                     NULL); 

    for (i =0; env[i]; i++) { 
        continue; 
    } 

    /* Write the request type (SSI "exec cmd" or cgi). */
    if (write(fd, &r_type, sizeof(int)) < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r,
                     "write to cgi daemon process");
    }

    /* Write the number of entries in the environment. */
    if (write(fd, &i, sizeof(int)) < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
        }     

    for (i = 0; env[i]; i++) { 
        data = apr_pstrcat(r->pool, data, env[i], "\n", NULL); 
    } 
    data = apr_pstrcat(r->pool, data, r->args, NULL); 
    len = strlen(data); 
    /* Write the length of the concatenated env string. */
    if (write(fd, &len, sizeof(int)) < 0) { 
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
    }
    /* Write the concatted env string. */     
    if (write(fd, data, len) < 0) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
    }
    /* Write module_index id value. */     
    if (write(fd, &core_module.module_index, sizeof(int)) < 0) { 
        ap_log_rerror(APLOG_MARK, APLOG_ERR, errno, r, 
                     "write to cgi daemon process"); 
    }     
    if (suexec_mod) {
        suexec_config_t *suexec_cfg = ap_get_module_config(r->per_dir_config,
                                                           suexec_mod);

        write(fd, &suexec_mod->module_index, sizeof(int));
        write(fd, suexec_cfg, sizeof(*suexec_cfg));
    }

#if 0
#ifdef RLIMIT_CPU 
    if (conf->limit_cpu) { 
        len = 1; 
        write(fd, &len, sizeof(int)); 
        write(fd, conf->limit_cpu, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        write(fd, &len, sizeof(int)); 
    } 
#endif 

#if defined(RLIMIT_DATA) || defined(RLIMIT_VMEM) || defined(RLIMIT_AS) 
    if (conf->limit_mem) { 
        len = 1; 
        write(fd, &len, sizeof(int)); 
        write(fd, conf->limit_mem, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        write(fd, &len, sizeof(int)); 
    } 
#endif 
  
#ifdef RLIMIT_NPROC 
    if (conf->limit_nproc) { 
        len = 1; 
        write(fd, &len, sizeof(int)); 
        write(fd, conf->limit_nproc, sizeof(struct rlimit)); 
    } 
    else { 
        len = 0; 
        write(fd, &len, sizeof(int)); 
    } 
#endif
#endif 
   /* send a minimal notes table */
   data  = (char *) apr_table_get(r->notes, "mod_userdir_user");
   if (data != NULL) {
       len = strlen(data);
       write(fd, &len, sizeof(len));
       write(fd, data, len);
   }
   else {
       len = 0;
       write(fd, &len, sizeof(len));
   }
}