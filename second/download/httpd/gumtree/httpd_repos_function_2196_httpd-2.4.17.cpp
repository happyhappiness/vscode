static int is_aborted(ap_filter_t *f)
{
    return (f->c->aborted);
}