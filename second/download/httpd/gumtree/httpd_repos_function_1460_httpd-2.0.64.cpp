static void *create_win32_dir_config(apr_pool_t *p, char *dir)
{
    win32_dir_conf *conf;
    conf = (win32_dir_conf*)apr_palloc(p, sizeof(win32_dir_conf));
    conf->script_interpreter_source = INTERPRETER_SOURCE_UNSET;
    return conf;
}