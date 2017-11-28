boolean
at_begline_loc_p(const char * pattern, const char *p, reg_syntax_t syntax)
{
    const char *prev = p - 2;
    boolean prev_prev_backslash = prev > pattern && prev[-1] == '\\';

    return
        /* After a subexpression?  */
        (*prev == '(' && (syntax & RE_NO_BK_PARENS || prev_prev_backslash))
        /* After an alternative?  */
        || (*prev == '|' && (syntax & RE_NO_BK_VBAR || prev_prev_backslash));
}