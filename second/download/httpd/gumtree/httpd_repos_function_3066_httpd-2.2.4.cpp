char *gen_install_name(const char *name, int genlib)
{
    struct stat sb;
    char *newname;
    int rv;

    newname = gen_library_name(name, genlib);

    /* Check if it exists. If not, return NULL.  */
    rv = stat(newname, &sb);

    if (rv) {
        return NULL;
    }

    return newname;
}