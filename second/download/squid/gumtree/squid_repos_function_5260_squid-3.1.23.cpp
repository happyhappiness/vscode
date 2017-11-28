static int
netdbLRU(const void *A, const void *B)
{
    const netdbEntry *const *n1 = (const netdbEntry *const *)A;
    const netdbEntry *const *n2 = (const netdbEntry *const *)B;

    if ((*n1)->last_use_time > (*n2)->last_use_time)
        return (1);

    if ((*n1)->last_use_time < (*n2)->last_use_time)
        return (-1);

    return (0);
}