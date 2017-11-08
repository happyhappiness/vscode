apr_status_t sed_init_commands(sed_commands_t *commands, sed_err_fn_t *errfn, void *data,
                               apr_pool_t *p)
{
    memset(commands, 0, sizeof(*commands));

    commands->errfn = errfn;
    commands->data = data;

    commands->labtab = commands->ltab;
    commands->lab = commands->labtab + 1;
    commands->pool = p;

    commands->respace = apr_pcalloc(p, RESIZE);
    if (commands->respace == NULL) {
        command_errf(commands, SEDERR_OOMMES);
        return APR_EGENERAL;
    }

    commands->rep = alloc_reptr(commands);
    if (commands->rep == NULL)
        return APR_EGENERAL;

    commands->rep->ad1 = commands->respace;
    commands->reend = &commands->respace[RESIZE - 1];
    commands->labend = &commands->labtab[SED_LABSIZE];
    commands->canbefinal = 1;

    return APR_SUCCESS;
}