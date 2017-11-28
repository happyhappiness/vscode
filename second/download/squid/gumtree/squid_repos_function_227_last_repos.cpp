static void
free_request(struct _request *r)
{
    if (r->url)
        free(r->url);
    free(r);
}