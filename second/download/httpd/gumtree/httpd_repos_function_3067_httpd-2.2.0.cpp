int explode_static_lib(const char *lib, command_t *cmd_data)
{
    char tmpdir[1024];
    char savewd[1024];
    char cmd[1024];
    const char *name;
    DIR *dir;
    struct dirent *entry;

    /* Bah! */
    if (cmd_data->options.dry_run) {
        return 0;
    }

    strcpy(tmpdir, lib);
    strcat(tmpdir, ".exploded");

    mkdir(tmpdir, 0);
    push_count_chars(cmd_data->tmp_dirs, strdup(tmpdir));
    getcwd(savewd, sizeof(savewd));

    if (chdir(tmpdir) != 0)
        return 1;

    strcpy(cmd, LIBRARIAN " x ");
    name = strrchr(lib, '/');

    if (name) {
        name++;
    } else {
        name = lib;
    }

    strcat(cmd, "../");
    strcat(cmd, name);
    system(cmd);
    chdir(savewd);
    dir = opendir(tmpdir);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            strcpy(cmd, tmpdir);
            strcat(cmd, "/");
            strcat(cmd, entry->d_name);
            push_count_chars(cmd_data->arglist, strdup(cmd));
        }
    }

    closedir(dir);
    return 0;
}