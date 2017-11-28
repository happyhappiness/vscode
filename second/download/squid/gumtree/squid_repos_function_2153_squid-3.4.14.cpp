static int
xprof_comp(xprof_stats_node ** ii, xprof_stats_node ** jj)
{
    if ((*ii)->hist.summ < (*jj)->hist.summ)
        return (1);

    if ((*ii)->hist.summ > (*jj)->hist.summ)
        return (-1);

    return (0);
}