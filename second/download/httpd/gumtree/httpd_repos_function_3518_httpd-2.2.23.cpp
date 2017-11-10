void add_linker_flag_prefix(count_chars *cc, const char *arg)
{
#ifndef LINKER_FLAG_PREFIX
    push_count_chars(cc, arg);
#else
    char *newarg;
    newarg = (char*)malloc(strlen(arg) + sizeof(LINKER_FLAG_PREFIX) + 1);
    strcpy(newarg, LINKER_FLAG_PREFIX);
    strcat(newarg, arg);
    push_count_chars(cc, newarg);
#endif
}