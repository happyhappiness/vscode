void cache_pq_dump(cache_pqueue_t *q,
                   FILE*out,
                   cache_pqueue_print_entry print)
{
    int i;

    fprintf(stdout,"posn\tleft\tright\tparent\tminchild\t...\n");
    for (i = 1; i < q->size ;i++) {
        fprintf(stdout,
                "%d\t%d\t%d\t%d\t%" APR_SSIZE_T_FMT "\t",
                i,
                left(i), right(i), parent(i),
                minchild(q, i));
        print(out, q->d[i]);
    }
}

/*
 * this is a debug function.. so it's EASY not fast
