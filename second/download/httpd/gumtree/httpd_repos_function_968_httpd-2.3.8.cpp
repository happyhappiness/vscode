static const char *register_map_to_storage_hook(cmd_parms *cmd, void *_cfg,
                                                const char *file,
                                                const char *function)
{
    return register_named_file_function_hook("map_to_storage", cmd, _cfg,
                                             file, function);
}