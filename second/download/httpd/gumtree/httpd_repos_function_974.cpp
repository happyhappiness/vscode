static const char *register_access_checker_hook(cmd_parms *cmd, void *_cfg,
                                                const char *file,
                                                const char *function)
{
    return register_named_file_function_hook("access_checker", cmd, _cfg,
                                             file, function);
}