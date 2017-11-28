static int			/* XXX: arbitrary ordering for non-contiguous masks */
rn_lexobetter(void *m_arg, void *n_arg)
{
    register u_char *mp = m_arg, *np = n_arg, *lim;

    if (*mp > *np)
        return 1;		/* not really, but need to check longer one first */
    if (*mp == *np)
        for (lim = mp + *mp; mp < lim;)
            if (*mp++ > *np++)
                return 1;
    return 0;
}