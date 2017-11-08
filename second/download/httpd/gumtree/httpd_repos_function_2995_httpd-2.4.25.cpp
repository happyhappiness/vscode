apr_status_t sed_compile_string(sed_commands_t *commands, const char *s)
{
    apr_status_t rv;

    commands->earg = s;
    commands->eflag = 1;

    rv = fcomp(commands, NULL);
    if (rv == APR_SUCCESS)
        commands->canbefinal = check_finalized(commands);

    commands->eflag = 0;

    return (rv != 0 ? APR_EGENERAL : APR_SUCCESS);
}