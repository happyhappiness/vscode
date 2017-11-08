static int check_headers_recursion(request_rec *r)
{
    void *check = NULL;
    apr_pool_userdata_get(&check, "check_headers_recursion", r->pool);
    if (check) {
        return 1;
    }
    apr_pool_userdata_setn("true", "check_headers_recursion", NULL, r->pool);
    return 0;
}