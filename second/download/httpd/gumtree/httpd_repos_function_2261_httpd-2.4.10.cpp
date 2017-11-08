static int substitute(sed_eval_t *eval, sed_reptr_t *ipc,
                      step_vars_storage *step_vars)
{
    if(match(eval, ipc->re1, 0, step_vars) == 0)    return(0);

    eval->numpass = 0;
    eval->sflag = 0;        /* Flags if any substitution was made */
    if (dosub(eval, ipc->rhs, ipc->gfl, step_vars) != APR_SUCCESS)
        return -1;

    if(ipc->gfl) {
        while(*step_vars->loc2) {
            if(match(eval, ipc->re1, 1, step_vars) == 0) break;
            if (dosub(eval, ipc->rhs, ipc->gfl, step_vars) != APR_SUCCESS)
                return -1;
        }
    }
    return(eval->sflag);
}