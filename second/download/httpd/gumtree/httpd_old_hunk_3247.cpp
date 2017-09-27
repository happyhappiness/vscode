
#define AP_MAX_ARGC 64

static const char *invoke_cmd(const command_rec *cmd, cmd_parms *parms,
                              void *mconfig, const char *args)
{
    char *w, *w2, *w3;
    const char *errmsg = NULL;

    if ((parms->override & cmd->req_override) == 0)
        return apr_pstrcat(parms->pool, cmd->name, " not allowed here", NULL);

    parms->info = cmd->cmd_data;
    parms->cmd = cmd;

    switch (cmd->args_how) {
    case RAW_ARGS:
