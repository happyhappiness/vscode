static void
hash_init(void)
{
    register struct tok *tp;
    register const char *cp;
    register int h;
    register int b;

    memset((char *) buckets, '\0', sizeof(buckets));
    for (tp = tokens; tp->name; tp++) {
        for (h = 0, cp = tp->name; *cp; cp++)
            h += *cp;
        tp->hash = h;
        b = BUCKET(h);
        if (buckets[b])
            tp->next = buckets[b];  /* BUG ??? */
        buckets[b] = tp;
    }
}