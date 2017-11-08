static apr_status_t varbuf_cleanup(void *info_)
{
    struct ap_varbuf_info *info = info_;
    info->node->next = NULL;
    apr_allocator_free(info->allocator, info->node);
    return APR_SUCCESS;
}