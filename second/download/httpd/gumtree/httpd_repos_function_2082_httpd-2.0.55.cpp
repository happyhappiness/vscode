static void clean_child_exit(int code)
{
    if (pchild)
        apr_pool_destroy(pchild);
    exit(code);
}