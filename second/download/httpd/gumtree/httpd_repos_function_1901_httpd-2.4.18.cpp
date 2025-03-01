static apr_status_t hm_readid(void* mem, void *data, apr_pool_t *p)
{
    hm_slot_server_t *old = (hm_slot_server_t *) mem;
    hm_slot_server_ctx_t *s = (hm_slot_server_ctx_t *) data;
    hm_server_t *new = s->s;
    if (strncmp(old->ip, new->ip, MAXIPSIZE)==0) {
        s->found = 1;
        s->item_id = old->id;
    }
    return APR_SUCCESS;
}