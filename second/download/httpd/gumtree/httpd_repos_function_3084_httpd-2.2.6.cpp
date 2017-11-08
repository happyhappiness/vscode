void add_dylink_noinstall(count_chars *cc, const char *arg, int pathlen,
                          int extlen)
{
    const char *install_path, *current_path, *name;
    char *exp_argument;
    int i_p_len, c_p_len, name_len, dyext_len, cur_len;

    install_path = load_install_path(arg);
    current_path = load_noinstall_path(arg, pathlen);

    if (!install_path || !current_path) {
        return;
    }

    push_count_chars(cc, DYNAMIC_LINK_NO_INSTALL);

    i_p_len = strlen(install_path);
    c_p_len = strlen(current_path);

    name = arg+pathlen;
    name_len = extlen-pathlen;
    dyext_len = sizeof(DYNAMIC_LIB_EXT) - 1;

    /* No, we need to replace the extension. */
    exp_argument = (char *)malloc(i_p_len + c_p_len + (name_len*2) +
                                  (dyext_len*2) + 2);

    cur_len = 0;
    strcpy(exp_argument, install_path);
    cur_len += i_p_len;
    exp_argument[cur_len++] = '/';
    strncpy(exp_argument+cur_len, name, extlen-pathlen);
    cur_len += name_len;
    strcpy(exp_argument+cur_len, DYNAMIC_LIB_EXT);
    cur_len += dyext_len;
    exp_argument[cur_len++] = ':';
    strcpy(exp_argument+cur_len, current_path);
    cur_len += c_p_len;
    exp_argument[cur_len++] = '/';
    strncpy(exp_argument+cur_len, name, extlen-pathlen);
    cur_len += name_len;
    strcpy(exp_argument+cur_len, DYNAMIC_LIB_EXT);
    cur_len += dyext_len;

    push_count_chars(cc, exp_argument);
}