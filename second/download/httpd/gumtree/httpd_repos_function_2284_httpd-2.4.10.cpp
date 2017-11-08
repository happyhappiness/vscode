static sed_reptr_t *alloc_reptr(sed_commands_t *commands)
{
    sed_reptr_t *var;

    var = apr_pcalloc(commands->pool, sizeof(sed_reptr_t));
    if (var == NULL) {
        command_errf(commands, SEDERR_OOMMES);
        return 0;
    }

    var->nrep = commands->nrep;
    var->findex = -1;
    commands->nrep++;

    if (commands->ptrspace == NULL)
        commands->ptrspace = var;
    else
        commands->ptrend->next = var;

    commands->ptrend = var;
    commands->labtab->address = var;
    return var;
}