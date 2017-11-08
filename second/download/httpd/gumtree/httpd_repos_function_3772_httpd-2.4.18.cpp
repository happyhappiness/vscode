static const char *set_sethandler(cmd_parms *cmd,
                                     void *d_,
                                     const char *arg_)
{
    core_dir_config *dirconf = d_;

    if (arg_ == ap_strstr_c(arg_, "proxy:unix")) { 
        dirconf->handler = arg_;
    }
    else { 
        char *arg = apr_pstrdup(cmd->pool,arg_);
        ap_str_tolower(arg);
        dirconf->handler = arg;
    }

    return NULL;
}