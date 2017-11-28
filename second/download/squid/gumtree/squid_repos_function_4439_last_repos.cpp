size_t
free_hostname_list(struct hstruct **hlist, size_t nhosts)
{
    struct hstruct *hp = NULL;
    size_t i;

    hp = *hlist;
    for (i = 0; i < nhosts; ++i) {
        xfree(hp[i].host);
    }

    safe_free(hp);
    *hlist = hp;
    return 0;
}