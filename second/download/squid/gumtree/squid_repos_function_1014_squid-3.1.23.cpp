static void
SetConfigFilename(char const *file_name, bool is_pipe)
{
    cfg_filename = file_name;

    char const *token;

    if (is_pipe)
        cfg_filename = file_name + 1;
    else if ((token = strrchr(cfg_filename, '/')))
        cfg_filename = token + 1;
}