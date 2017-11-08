bool parse_output_file_name(char *arg, cmd_data_t *cmd_data)
{
    char *name = strrchr(arg, '/');
    char *ext = strrchr(arg, '.');
    char *newarg = NULL, *newext;
    int pathlen;

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

    if (!ext) {
        cmd_data->stub_name = arg;
        cmd_data->output_type = otProgram;
        newarg = (char *)malloc(strlen(arg) + 5);
        strcpy(newarg, arg);
        strcat(newarg, EXE_EXT);
        cmd_data->arglist[cmd_data->num_args++] = newarg;
        cmd_data->output_name = newarg;
        return true;
    }

    ext++;
    pathlen = name - arg;

    if (strcmp(ext, "la") == 0) {
        cmd_data->stub_name = arg;
        cmd_data->output_type = shared ? otDynamicLibrary : otStaticLibrary;
        newarg = (char *)malloc(strlen(arg) + 10);
        mkdir(".libs", 0);
        strcpy(newarg, ".libs/");

        if (strncmp(arg, "lib", 3) == 0) {
            arg += 3;
        }

        strcat(newarg, arg);
        newext = strrchr(newarg, '.') + 1;
        strcpy(newext, shared ? DYNAMIC_LIB_EXT : STATIC_LIB_EXT);

#ifdef TRUNCATE_DLL_NAME
        if (shared) {
          newarg = truncate_dll_name(newarg);
        }
#endif

        cmd_data->arglist[cmd_data->num_args++] = newarg;
        cmd_data->output_name = newarg;
        return true;
    }

    if (strcmp(ext, "lo") == 0) {
        cmd_data->stub_name = arg;
        cmd_data->output_type = otObject;
        newarg = (char *)malloc(strlen(arg) + 2);
        strcpy(newarg, arg);
        ext = strrchr(newarg, '.') + 1;
        strcpy(ext, OBJECT_EXT);
        cmd_data->arglist[cmd_data->num_args++] = newarg;
        cmd_data->output_name = newarg;
        return true;
    }

    return false;
}