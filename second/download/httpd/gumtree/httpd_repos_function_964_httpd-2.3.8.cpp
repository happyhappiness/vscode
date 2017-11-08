static const char *register_translate_name_hook(cmd_parms *cmd, void *_cfg,
                                                const char *file,
                                                const char *function)
{
    return register_named_file_function_hook("translate_name", cmd, _cfg,
                                             file, function);
}