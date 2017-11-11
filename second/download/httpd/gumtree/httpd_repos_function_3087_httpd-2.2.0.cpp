bool explode_static_lib(char *lib, cmd_data_t *cmd_data)
{
    char tmpdir[1024];
    char savewd[1024];
    char cmd[1024];
    char *name;
    DIR *dir;
    struct dirent *entry;

    strcpy(tmpdir, lib);
    strcat(tmpdir, ".exploded");

    mkdir(tmpdir, 0);
    cmd_data->tmp_dirs[cmd_data->num_tmp_dirs++] = strdup(tmpdir);
    getcwd(savewd, sizeof(savewd));

    if (chdir(tmpdir) != 0)
        return false;

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
            cmd_data->arglist[cmd_data->num_args++] = strdup(cmd);
        }
    }

    closedir(dir);
    return true;
}