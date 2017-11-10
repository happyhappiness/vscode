static apr_status_t dosub(sed_eval_t *eval, char *rhsbuf, int n,
                          step_vars_storage *step_vars)
{
    char *lp, *sp, *rp;
    int c;
    apr_status_t rv = APR_SUCCESS;

    if(n > 0 && n < 999) {
        eval->numpass++;
        if(n != eval->numpass) return APR_SUCCESS;
    }
    eval->sflag = 1;
    lp = eval->linebuf;
    sp = eval->genbuf;
    rp = rhsbuf;
    sp = place(eval, sp, lp, step_vars->loc1);
    while ((c = *rp++) != 0) {
        if (c == '&') {
            sp = place(eval, sp, step_vars->loc1, step_vars->loc2);
            if (sp == NULL)
                return APR_EGENERAL;
        }
        else if (c == '\\') {
            c = *rp++;
            if (c >= '1' && c < NBRA+'1') {
                sp = place(eval, sp, step_vars->braslist[c-'1'],
                           step_vars->braelist[c-'1']);
                if (sp == NULL)
                    return APR_EGENERAL;
            }
            else
                *sp++ = c;
          } else
            *sp++ = c;
        if (sp >= eval->genbuf + eval->gsize) {
            /* expand genbuf and set the sp appropriately */
            grow_gen_buffer(eval, eval->gsize + 1024, &sp);
        }
    }
    lp = step_vars->loc2;
    step_vars->loc2 = sp - eval->genbuf + eval->linebuf;
    append_to_genbuf(eval, lp, &sp);
    copy_to_linebuf(eval, eval->genbuf);
    return rv;
}