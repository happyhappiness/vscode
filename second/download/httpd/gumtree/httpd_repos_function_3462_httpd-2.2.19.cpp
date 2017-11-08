char *gen_library_name(const char *name, int genlib)
{
    char *newarg, *newext;

    newarg = (char *)malloc(strlen(name) + 11);
    strcpy(newarg, ".libs/");

    if (genlib == 2 && strncmp(name, "lib", 3) == 0) {
        name += 3;
    }

    if (genlib == 2) {
        strcat(newarg, jlibtool_basename(name));
    }
    else {
        strcat(newarg, name);
    }

    newext = strrchr(newarg, '.') + 1;

    switch (genlib) {
    case 0:
        strcpy(newext, STATIC_LIB_EXT);
        break;
    case 1:
        strcpy(newext, DYNAMIC_LIB_EXT);
        break;
    case 2:
        strcpy(newext, MODULE_LIB_EXT);
        break;
    }

    return newarg;
}