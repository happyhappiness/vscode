static int
xprof_comp(const void *A, const void *B)
{
    const xprof_stats_node *ii = *(static_cast<const xprof_stats_node * const *>(A));
    const xprof_stats_node *jj = *(static_cast<const xprof_stats_node * const *>(B));

    if (ii->hist.summ < jj->hist.summ)
        return (1);

    if (ii->hist.summ > jj->hist.summ)
        return (-1);

    return (0);
}