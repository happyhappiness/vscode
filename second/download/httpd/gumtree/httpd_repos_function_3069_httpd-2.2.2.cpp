int parse_output_file_name(char *arg, command_t *cmd_data)
{
    char *name = strrchr(arg, '/');
    char *ext = strrchr(arg, '.');
    char *newarg = NULL;
    int pathlen;

    cmd_data->fake_output_name = arg;

    if (name) {
        name++;
    }
    else {
        name = strrchr(arg, '\\');

        if (name == NULL) {
            name = arg;
        }
        else {
            name++;
        }
    }

    if (!ext) {
        cmd_data->basename = arg;
        cmd_data->output = otProgram;
#if defined(_OSD_POSIX)
        cmd_data->options.pic_mode = pic_AVOID;
#endif
        newarg = (char *)malloc(strlen(arg) + 5);
        strcpy(newarg, arg);
#ifdef EXE_EXT
        strcat(newarg, EXE_EXT);
#endif
        cmd_data->output_name = newarg;
        return 1;
    }

    ext++;
    pathlen = name - arg;

    if (strcmp(ext, "la") == 0) {
        assert(cmd_data->mode == mLink);

        cmd_data->basename = arg;
        cmd_data->static_name.normal = gen_library_name(arg, 0);
        cmd_data->shared_name.normal = gen_library_name(arg, 1);
        cmd_data->module_name.normal = gen_library_name(arg, 2);
        cmd_data->static_name.install = gen_install_name(arg, 0);
        cmd_data->shared_name.install = gen_install_name(arg, 1);
        cmd_data->module_name.install = gen_install_name(arg, 2);

#ifdef TRUNCATE_DLL_NAME
        if (shared) {
          arg = truncate_dll_name(arg);
        }
#endif

        cmd_data->output_name = arg;
        return 1;
    }

    if (strcmp(ext, "lo") == 0) {
        cmd_data->basename = arg;
        cmd_data->output = otObject;
        newarg = (char *)malloc(strlen(arg) + 2);
        strcpy(newarg, arg);
        ext = strrchr(newarg, '.') + 1;
        strcpy(ext, OBJECT_EXT);
        cmd_data->output_name = newarg;
        return 1;
    }

    return 0;
}