    strcpy(newarg, LINKER_FLAG_PREFIX);
    strcat(newarg, arg);
    push_count_chars(cc, newarg);
#endif
}

int parse_input_file_name(char *arg, command_t *cmd_data)
{
    char *ext = strrchr(arg, '.');
    char *name = strrchr(arg, '/');
    int pathlen;
    enum lib_type libtype;
