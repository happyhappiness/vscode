static __inline void
#else
static inline void
#endif
xprof_update(xprof_stats_data * head)
{
    if (head->delta < head->best)
        head->best = head->delta;
    if (head->worst < head->delta)
        head->worst = head->delta;
    head->summ += head->delta;
    head->count++;
}