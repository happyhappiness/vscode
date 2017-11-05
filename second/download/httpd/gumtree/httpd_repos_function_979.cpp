static const char *register_quick_hook(cmd_parms *cmd, void *_cfg,
                                       const char *file, const char *function)
{
    return register_named_file_function_hook("quick", cmd, _cfg, file,
                                             function);
}