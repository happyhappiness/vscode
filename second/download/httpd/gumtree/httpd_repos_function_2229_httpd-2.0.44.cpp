static void clean_child_exit(int code)
{
    if (pchild) {
        apr_pool_destroy(pchild);
    }
    ap_mpm_pod_close(pod);
    exit(code);
}