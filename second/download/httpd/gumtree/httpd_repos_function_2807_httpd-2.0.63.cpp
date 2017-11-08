int wmain(int argc, const wchar_t **wargv, const wchar_t **wenv)
{
    char **argv;
    char **env;
    int dupenv;

    (void)apr_wastrtoastr(&argv, wargv, argc);

    dupenv = apr_wastrtoastr(&env, wenv, -1);

    _environ = _malloc_dbg((dupenv + 1) * sizeof (char *), 
                           _CRT_BLOCK, __FILE__, __LINE__ );
    memcpy(_environ, env, (dupenv + 1) * sizeof (char *));

    /* MSVCRT will attempt to maintain the wide environment calls
     * on _putenv(), which is bogus if we've passed a non-ascii
     * string to _putenv(), since they use MultiByteToWideChar
     * and breaking the implicit utf-8 assumption we've built.
     *
     * Reset _wenviron for good measure.
     */
    if (_wenviron) {
        wenv = _wenviron;
        _wenviron = NULL;
        free((wchar_t **)wenv);
    }

    apr_app_init_complete = 1;

    return main(argc, argv, env);
}