static int
sortByRtt(const void *A, const void *B)
{
    const netdbEntry *const *n1 = (const netdbEntry *const *)A;
    const netdbEntry *const *n2 = (const netdbEntry *const *)B;

    if ((*n1)->rtt > (*n2)->rtt)
        return 1;
    else if ((*n1)->rtt < (*n2)->rtt)
        return -1;
    else
        return 0;
}