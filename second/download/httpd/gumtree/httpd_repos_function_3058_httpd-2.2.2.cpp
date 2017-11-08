char *check_object_exists(command_t *cmd, const char *arg, int arglen)
{
    char *newarg, *ext;
    int pass, rv;

    newarg = (char *)malloc(arglen + 10);
    memcpy(newarg, arg, arglen);
    newarg[arglen] = 0;
    ext = newarg + arglen;

    pass = 0;

    do {
        struct stat sb;

        switch (pass) {
        case 0:
            strcpy(ext, OBJECT_EXT);
            break;
/*
        case 1:
            strcpy(ext, NO_PIC_EXT);
            break;
*/
        default:
            break;
        } 

        if (!cmd->options.silent) {
            printf("Checking (obj): %s\n", newarg);
        }
        rv = stat(newarg, &sb);
    }
    while (rv != 0 && ++pass < 1);

    if (rv == 0) {
        if (pass == 1) {
            cmd->options.pic_mode = pic_AVOID;
        }
        return newarg;
    }

    return NULL;
}