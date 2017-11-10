void cache_pq_dump(cache_pqueue_t *q,
                   FILE*out,
                   cache_pqueue_print_entry print)
{
    int i;

    fprintf(stdout,"posn\tleft\tright\tparent\tmaxchild\t...\n");
    for (i = 1; i < q->size ;i++) {
        fprintf(stdout,
                "%d\t%d\t%d\t%d\t%" APR_SSIZE_T_FMT "\t",
                i,
                left(i), right(i), parent(i),
                maxchild(q, i));
        print(out, q->d[i]);
    }
}