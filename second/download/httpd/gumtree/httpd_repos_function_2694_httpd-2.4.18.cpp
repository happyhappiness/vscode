static int match(sed_eval_t *eval, char *expbuf, int gf,
                 step_vars_storage *step_vars)
{
    char   *p1;
    int circf;

    if(gf) {
        if(*expbuf)    return(0);
        step_vars->locs = p1 = step_vars->loc2;
    } else {
        p1 = eval->linebuf;
        step_vars->locs = 0;
    }

    circf = *expbuf++;
    return(sed_step(p1, expbuf, circf, step_vars));
}