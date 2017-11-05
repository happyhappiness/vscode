static void *merge_win32_dir_configs(apr_pool_t *p, void *basev, void *addv)
{
    win32_dir_conf *new;
    win32_dir_conf *base = (win32_dir_conf *) basev;
    win32_dir_conf *add = (win32_dir_conf *) addv;

    new = (win32_dir_conf *) apr_pcalloc(p, sizeof(win32_dir_conf));
    new->script_interpreter_source = (add->script_interpreter_source
                                           != INTERPRETER_SOURCE_UNSET)
                                   ? add->script_interpreter_source
                                   : base->script_interpreter_source;
    return new;
}