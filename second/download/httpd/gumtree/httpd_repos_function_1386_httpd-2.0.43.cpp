static const char *set_interpreter_source(cmd_parms *cmd, void *dv,
                                          char *arg)
{
    win32_dir_conf *d = (win32_dir_conf *)dv;
    if (!strcasecmp(arg, "registry")) {
        d->script_interpreter_source = INTERPRETER_SOURCE_REGISTRY;
    }
    else if (!strcasecmp(arg, "registry-strict")) {
        d->script_interpreter_source = INTERPRETER_SOURCE_REGISTRY_STRICT;
    }
    else if (!strcasecmp(arg, "script")) {
        d->script_interpreter_source = INTERPRETER_SOURCE_SHEBANG;
    }
    else {
        return apr_pstrcat(cmd->temp_pool, "ScriptInterpreterSource \"", arg, 
                           "\" must be \"registry\", \"registry-strict\" or "
                           "\"script\"", NULL);
    }
    return NULL;
}