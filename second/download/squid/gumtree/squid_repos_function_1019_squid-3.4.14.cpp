static void
SetConfigFilename(char const *file_name, bool is_pipe)
{
    if (is_pipe)
        cfg_filename = file_name + 1;
    else
        cfg_filename = file_name;
}