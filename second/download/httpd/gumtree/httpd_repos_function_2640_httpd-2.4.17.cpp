static const char* set_skipto(cmd_parms* cmd, void* CFG, const char* arg)
{
    tattr* attr;
    xml2cfg* cfg = CFG;
    if (cfg->skipto == NULL)
        cfg->skipto = apr_array_make(cmd->pool, 4, sizeof(tattr));
    attr = apr_array_push(cfg->skipto) ;
    attr->val = arg;
    return NULL;
}