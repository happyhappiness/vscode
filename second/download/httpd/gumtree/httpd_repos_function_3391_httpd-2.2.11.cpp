void add_minus_l(count_chars *cc, const char *arg)
{
    char *newarg;
    char *name = strrchr(arg, '/');
    char *file = strrchr(arg, '.');
    char *lib  = strstr(name, "lib");

    if (name !=NULL && file != NULL && lib == name+1) {
        *name = '\0';
        *file = '\0';
        file = name;
        file = file+4;
        push_count_chars(cc, "-L");
        push_count_chars(cc, arg);
        /* we need one argument like -lapr-1 */
        newarg = malloc(strlen(file) + 3);
        strcpy(newarg, "-l");
        strcat(newarg, file);
        push_count_chars(cc, newarg);
    } else {
        push_count_chars(cc, arg);
    }
}