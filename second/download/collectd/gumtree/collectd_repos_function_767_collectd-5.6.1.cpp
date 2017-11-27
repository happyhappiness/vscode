static int redis_handle_query (redisContext *rh, redis_node_t *rn, redis_query_t *rq) /* {{{ */
{
    redisReply *rr;
    const data_set_t *ds;
    value_t val;

    ds = plugin_get_ds (rq->type);
    if (!ds) {
        ERROR ("redis plugin: DataSet `%s' not defined.", rq->type);
        return (-1);
    }

    if (ds->ds_num != 1) {
        ERROR ("redis plugin: DS `%s' has too many types.", rq->type);
        return (-1);
    }

    if ((rr = redisCommand(rh, rq->query)) == NULL) {
        WARNING("redis plugin: unable to carry out query `%s'.", rq->query);
        return (-1);
    }

    switch (rr->type) {
    case REDIS_REPLY_INTEGER:
        switch (ds->ds[0].type) {
        case DS_TYPE_COUNTER:
            val.counter = (counter_t)rr->integer;
            break;
        case DS_TYPE_GAUGE:
            val.gauge = (gauge_t)rr->integer;
            break;
        case DS_TYPE_DERIVE:
            val.gauge = (derive_t)rr->integer;
            break;
        case DS_TYPE_ABSOLUTE:
            val.gauge = (absolute_t)rr->integer;
            break;
        }
        break;
    case REDIS_REPLY_STRING:
        if (parse_value (rr->str, &val, ds->ds[0].type) == -1) {
            WARNING("redis plugin: Unable to parse field `%s'.", rq->type);
            freeReplyObject (rr);
            return (-1);
        }
        break;
    default:
        WARNING("redis plugin: Cannot coerce redis type.");
        freeReplyObject(rr);
        return (-1);
    }

    redis_submit(rn->name, rq->type, (strlen(rq->instance) >0)?rq->instance:NULL, val);
    freeReplyObject (rr);
    return 0;
}