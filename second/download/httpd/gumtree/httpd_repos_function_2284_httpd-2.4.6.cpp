static const char* set_alias(cmd_parms* cmd, void* CFG,
                             const char* charset, const char* alias)
{
    const char* errmsg = ap_check_cmd_context(cmd, GLOBAL_ONLY);
    if (errmsg != NULL)
        return errmsg ;
    else if (xmlAddEncodingAlias(charset, alias) == 0)
        return NULL;
    else
        return "Error setting charset alias";
}