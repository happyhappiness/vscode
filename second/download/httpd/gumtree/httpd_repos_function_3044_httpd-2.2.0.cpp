void print_config()
{
#ifdef LD_RUN_PATH
    printf("runpath_var=%s\n", LD_RUN_PATH);
#endif
#ifdef LD_LIBRARY_PATH
    printf("shlibpath_var=%s\n", LD_LIBRARY_PATH);
#endif
#ifdef SHELL_CMD
    printf("SHELL=\"%s\"\n", SHELL_CMD);
#endif
}