static int
compare_hosts(struct hstruct *host1, struct hstruct *host2)
{
    /*
     *
     * The comparison function must return an integer less than,  equal  to,
     * or  greater  than  zero  if  the  first  argument is considered to be
     * respectively less than, equal to, or greater than the second.
     */
    if ((host1->priority < host2->priority) && (host1->priority != -1))
        return -1;
    if ((host1->priority < host2->priority) && (host1->priority == -1))
        return 1;
    if ((host1->priority > host2->priority) && (host2->priority != -1))
        return 1;
    if ((host1->priority > host2->priority) && (host2->priority == -1))
        return -1;
    if (host1->priority == host2->priority) {
        if (host1->weight > host2->weight)
            return -1;
        if (host1->weight < host2->weight)
            return 1;
    }
    return 0;
}