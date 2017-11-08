apr_status_t sed_compile_file(sed_commands_t *commands, apr_file_t *fin)
{
    apr_status_t rv = fcomp(commands, fin);
    return (rv != 0 ? APR_EGENERAL : APR_SUCCESS);
}