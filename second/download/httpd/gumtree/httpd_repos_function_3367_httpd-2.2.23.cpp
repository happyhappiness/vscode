static void check_not_already_free(node_header_t *node)
{
    apr_bucket_alloc_t *list = node->alloc;
    node_header_t *curr = list->freelist;

    while (curr) {
        if (node == curr) {
            abort();
        }
        curr = curr->next;
    }
}