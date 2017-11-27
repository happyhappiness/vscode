static redis_query_t *redis_config_query (oconfig_item_t *ci) /* {{{ */
{
    redis_query_t *rq;
    int status;

    rq = calloc(1, sizeof(*rq));
    if (rq == NULL) {
        ERROR("redis plugin: calloc failed adding redis_query.");
        return NULL;
    }
    status = cf_util_get_string_buffer(ci, rq->query, sizeof(rq->query));
    if (status != 0)
        goto err;

    /*
     * Default to a gauge type.
     */
    (void)strncpy(rq->type, "gauge", sizeof(rq->type));
    (void)sstrncpy(rq->instance, rq->query, sizeof(rq->instance));
    replace_special(rq->instance, sizeof(rq->instance));

    for (int i = 0; i < ci->children_num; i++) {
        oconfig_item_t *option = ci->children + i;

        if (strcasecmp("Type", option->key) == 0) {
            status = cf_util_get_string_buffer(option, rq->type, sizeof(rq->type));
        } else if (strcasecmp("Instance", option->key) == 0) {
            status = cf_util_get_string_buffer(option, rq->instance, sizeof(rq->instance));
        } else {
            WARNING("redis plugin: unknown configuration option: %s", option->key);
            status = -1;
        }
        if (status != 0)
            goto err;
    }
    return rq;
 err:
    free(rq);
    return NULL;
}