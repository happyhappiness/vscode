boolean
at_endline_loc_p(const char *p, const char *pend, int syntax)
{
    const char *next = p;
    boolean next_backslash = *next == '\\';
    const char *next_next = p + 1 < pend ? p + 1 : NULL;

    return
        /* Before a subexpression?  */
        (syntax & RE_NO_BK_PARENS ? *next == ')'
         : next_backslash && next_next && *next_next == ')')
        /* Before an alternative?  */
        || (syntax & RE_NO_BK_VBAR ? *next == '|'
            : next_backslash && next_next && *next_next == '|');
}