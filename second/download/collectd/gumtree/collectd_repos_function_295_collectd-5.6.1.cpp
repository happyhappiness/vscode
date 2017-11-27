static int kafka_write(const data_set_t *ds, /* {{{ */
          const value_list_t *vl,
          user_data_t *ud)
{
    int      status = 0;
    void    *key;
    size_t   keylen = 0;
    char     buffer[8192];
    size_t   bfree = sizeof(buffer);
    size_t   bfill = 0;
    size_t   blen = 0;
    struct   kafka_topic_context  *ctx = ud->data;

    if ((ds == NULL) || (vl == NULL) || (ctx == NULL))
        return EINVAL;

    pthread_mutex_lock (&ctx->lock);
    status = kafka_handle(ctx);
    pthread_mutex_unlock (&ctx->lock);
    if( status != 0 )
        return status;

    bzero(buffer, sizeof(buffer));

    switch (ctx->format) {
    case KAFKA_FORMAT_COMMAND:
        status = create_putval(buffer, sizeof(buffer), ds, vl);
        if (status != 0) {
            ERROR("write_kafka plugin: create_putval failed with status %i.",
                  status);
            return status;
        }
        blen = strlen(buffer);
        break;
    case KAFKA_FORMAT_JSON:
        format_json_initialize(buffer, &bfill, &bfree);
        format_json_value_list(buffer, &bfill, &bfree, ds, vl,
                               ctx->store_rates);
        format_json_finalize(buffer, &bfill, &bfree);
        blen = strlen(buffer);
        break;
    case KAFKA_FORMAT_GRAPHITE:
        status = format_graphite(buffer, sizeof(buffer), ds, vl,
                                 ctx->prefix, ctx->postfix, ctx->escape_char,
                                 ctx->graphite_flags);
        if (status != 0) {
            ERROR("write_kafka plugin: format_graphite failed with status %i.",
                  status);
            return status;
        }
        blen = strlen(buffer);
        break;
    default:
        ERROR("write_kafka plugin: invalid format %i.", ctx->format);
        return -1;
    }

    key = ctx->key;
    if (key != NULL)
        keylen = strlen (key);
    else
        keylen = 0;

    rd_kafka_produce(ctx->topic, RD_KAFKA_PARTITION_UA,
                     RD_KAFKA_MSG_F_COPY, buffer, blen,
                     key, keylen, NULL);

    return status;
}