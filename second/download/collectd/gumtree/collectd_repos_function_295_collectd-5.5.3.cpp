static void kafka_topic_context_free(void *p) /* {{{ */
{
	struct kafka_topic_context *ctx = p;

	if (ctx == NULL)
		return;

    if (ctx->topic_name != NULL)
        sfree(ctx->topic_name);
    if (ctx->topic != NULL)
        rd_kafka_topic_destroy(ctx->topic);
    if (ctx->conf != NULL)
        rd_kafka_topic_conf_destroy(ctx->conf);
    if (ctx->kafka_conf != NULL)
        rd_kafka_conf_destroy(ctx->kafka_conf);
    if (ctx->kafka != NULL)
        rd_kafka_destroy(ctx->kafka);

    sfree(ctx);
}