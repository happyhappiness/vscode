int sed_step(char *p1, char *p2, int circf, step_vars_storage *vars)
{
    int c;


    if (circf) {
        vars->loc1 = p1;
        return (_advance(p1, p2, vars));
    }
    /* fast check for first character */
    if (*p2 == CCHR) {
        c = p2[1];
        do {
            if (*p1 != c)
                continue;
            if (_advance(p1, p2, vars)) {
                vars->loc1 = p1;
                return (1);
            }
        } while (*p1++);
        return (0);
    }
        /* regular algorithm */
    do {
        if (_advance(p1, p2, vars)) {
            vars->loc1 = p1;
            return (1);
        }
    } while (*p1++);
    return (0);
}