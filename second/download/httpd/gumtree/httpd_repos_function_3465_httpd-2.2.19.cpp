char *check_library_exists(command_t *cmd, const char *arg, int pathlen,
                           int libdircheck, enum lib_type *libtype)
{
    char *newarg, *ext;
    int pass, rv, newpathlen;

    newarg = (char *)malloc(strlen(arg) + 10);
    strcpy(newarg, arg);
    newarg[pathlen] = 0;

    newpathlen = pathlen;
    if (libdircheck) {
        strcat(newarg, ".libs/");
        newpathlen += sizeof(".libs/") - 1;
    }

    strcpy(newarg+newpathlen, arg+pathlen);
    ext = strrchr(newarg, '.') + 1;

    pass = 0;

    do {
        struct stat sb;

        switch (pass) {
        case 0:
            if (cmd->options.pic_mode != pic_AVOID &&
                cmd->options.shared != share_STATIC) {
                strcpy(ext, DYNAMIC_LIB_EXT);
                *libtype = type_DYNAMIC_LIB;
                break;
            }
            pass = 1;
            /* Fall through */
        case 1:
            strcpy(ext, STATIC_LIB_EXT);
            *libtype = type_STATIC_LIB;
            break;
        case 2:
            strcpy(ext, MODULE_LIB_EXT);
            *libtype = type_MODULE_LIB;
            break;
        case 3:
            strcpy(ext, OBJECT_EXT);
            *libtype = type_OBJECT;
            break;
        default:
            *libtype = type_UNKNOWN;
            break;
        } 

        if (!cmd->options.silent) {
            printf("Checking (lib): %s\n", newarg);
        }
        rv = stat(newarg, &sb);
    }
    while (rv != 0 && ++pass < 4);

    if (rv == 0) {
        return newarg;
    }

    return NULL;
}