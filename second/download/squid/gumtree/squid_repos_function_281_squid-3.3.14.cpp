int
free_hostname_list(struct hstruct **hlist, int nhosts)
{
    struct hstruct *hp = NULL;
    int i;

    hp = *hlist;
    for (i = 0; i < nhosts; ++i) {
        if (hp[i].host)
            xfree(hp[i].host);
        hp[i].host = NULL;
    }

    if (hp)
        xfree(hp);
    hp = NULL;
    *hlist = hp;
    return 0;
}