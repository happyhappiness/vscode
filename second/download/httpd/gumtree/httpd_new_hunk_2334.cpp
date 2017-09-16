    return res;

}



API_EXPORT(int) ap_cfg_closefile(configfile_t *cfp)

{

#ifdef DEBUG

    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, NULL, 

        "Done with config file %s", cfp->name);

#endif

    return (cfp->close == NULL) ? 0 : cfp->close(cfp->param);

}



/* Common structure that holds the file and pool for ap_pcfg_openfile */

typedef struct {

