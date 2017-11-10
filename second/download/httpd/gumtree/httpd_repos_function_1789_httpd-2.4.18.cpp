static const char *set_script_timeout(cmd_parms *cmd, void *dummy, const char *arg)
{
    cgid_dirconf *dc = dummy;

    if (ap_timeout_parameter_parse(arg, &dc->timeout, "s") != APR_SUCCESS) { 
        return "CGIDScriptTimeout has wrong format";
    }
 
    return NULL;
}