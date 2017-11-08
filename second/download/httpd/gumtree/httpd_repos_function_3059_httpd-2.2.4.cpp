void add_runtimedirlib(char *arg, command_t *cmd_data)
{
#ifdef RPATH
    add_rpath(cmd_data->shared_opts.dependencies, arg);
#else
#endif
}