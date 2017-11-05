static int hb_server_sort(const void *a_, const void *b_)
{
    hb_server_t *a = (hb_server_t*)a_;
    hb_server_t *b = (hb_server_t*)b_;
    if (a->ready == b->ready) {
        return 0;
    }
    else if (a->ready > b->ready) {
        return -1;
    }
    else {
        return 1;
    }
}