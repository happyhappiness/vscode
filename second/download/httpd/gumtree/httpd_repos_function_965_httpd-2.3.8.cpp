static const char *register_translate_name_block(cmd_parms *cmd, void *_cfg,
                                                 const char *line)
{
    return register_named_block_function_hook("translate_name", cmd, _cfg,
                                              line);
}