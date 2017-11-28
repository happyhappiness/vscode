float
calc_heap_skew(heap * heap, int replace)
{
    heap_node **nodes;
    long id, diff, skew = 0;
#ifdef  HEAP_DEBUG_SKEW
    long skewsq = 0;
#endif /* HEAP_DEBUG_SKEW */
    float norm = 0;
    unsigned long max;

    /*
     * Lock the heap to copy it.  If replacing it need to keep the heap locked
     * until we are all done.
     */
    mutex_lock(hp->lock);

    max = heap_nodes(heap);

    /*
     * Copy the heap nodes to a new storage area for offline sorting.
     */
    nodes = xmalloc(max * sizeof(heap_node *));
    memcpy(nodes, heap->nodes, max * sizeof(heap_node *));

    if (replace == 0) {
        /*
         * Unlock the heap to allow updates from other threads before the sort.
         * This allows other heap operations to proceed concurrently with the
         * heap skew computation on the heap at the time of the call ...
         */
        mutex_unlock(hp->lock);
    }
    qsort(nodes, max, sizeof(heap_node *), compare_heap_keys);

    for (id = 0; id < max; id++) {
        diff = id - nodes[id]->id;
        skew += abs(diff);

#ifdef  HEAP_DEBUG_SKEW
        skewsq += diff * diff;
#ifdef  HEAP_DEBUG_ALL
        printf("%d\tKey = %f, diff = %d\n", id, nodes[id]->key, diff);
#endif /* HEAP_DEBUG */
#endif /* HEAP_DEBUG_SKEW */
    }

    if (replace != 0) {
        /*
         * Replace the original heap with the newly sorted heap and let it
         * continue.  Then compute the skew using the copy of the previous heap
         * which we maintain as private data.
         */
        memcpy(heap->nodes, nodes, max * sizeof(heap_node *));

        for (id = 0; id < max; id++) {
            /*
             * Fix up all the ID values in the copied nodes.
             */
            heap->nodes[id]->id = id;
        }

        mutex_unlock(hp->lock);
    }
    /*
     * The skew value is normalized to a range of [0..1]; the distribution
     * appears to be a skewed Gaussian distribution.  For random insertions
     * into a heap the normalized skew will be slightly less than 0.5.  The
     * maximum value of skew/N^2 (for any value of N) is about 0.39 and is
     * fairly stable.
     */
    norm = skew * 2.56 / (max * max);

    /*
     * Free the nodes array; note this is just an array of pointers, not data!
     */
    xfree(nodes);
    return norm;
}