bool parse_input_file_name(char *arg, cmd_data_t *cmd_data)
{
    char *ext = strrchr(arg, '.');
    char *name = strrchr(arg, '/');
    char *newarg;

    if (!ext) {
        return false;
    }

    ext++;

    if (name == NULL) {
        name = strrchr(arg, '\\');

        if (name == NULL) {
            name = arg;
        } else {
            name++;
        }
    } else {
        name++;
    }

    if (strcmp(ext, "lo") == 0) {
        newarg = (char *)malloc(strlen(arg) + 10);
        strcpy(newarg, arg);
        strcpy(newarg + (ext - arg), OBJECT_EXT);
        cmd_data->arglist[cmd_data->num_args++] = newarg;
        cmd_data->obj_files[cmd_data->num_obj_files++] = newarg;
        return true;
    }

    if (strcmp(ext, "la") == 0) {
        newarg = (char *)malloc(strlen(arg) + 10);
        strcpy(newarg, arg);
        newarg[pathlen] = 0;
        strcat(newarg, ".libs/");

        if (strncmp(name, "lib", 3) == 0) {
            name += 3;
        }

        strcat(newarg, name);
        ext = strrchr(newarg, '.') + 1;

        if (shared && cmd_data->mode == mInstall) {
          strcpy(ext, DYNAMIC_LIB_EXT);
          newarg = truncate_dll_name(newarg);
        } else {
          strcpy(ext, STATIC_LIB_EXT);
        }

        cmd_data->arglist[cmd_data->num_args++] = newarg;
        return true;
    }

    if (strcmp(ext, "c") == 0) {
        if (cmd_data->stub_name == NULL) {
            cmd_data->stub_name = (char *)malloc(strlen(arg) + 4);
            strcpy(cmd_data->stub_name, arg);
            strcpy(strrchr(cmd_data->stub_name, '.') + 1, "lo");
        }
    }

    if (strcmp(name, CC) == 0 || strcmp(name, CC EXE_EXT) == 0) {
        if (cmd_data->output_type == otGeneral) {
            cmd_data->output_type = otObject;
        }
    }

    return false;
}