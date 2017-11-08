static APR_INLINE int skiplist_height(const apr_skiplist *sl)
{
    /* Skiplists (even empty) always have a top node, although this
     * implementation defers its creation until the first insert, or
     * deletes it with the last remove. We want the real height here.
     */
    return sl->height ? sl->height : 1;
}