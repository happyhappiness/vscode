static int kafka_handle(struct kafka_topic_context *ctx) /* {{{ */
{
    char                         errbuf[1024];
    rd_kafka_conf_t             *conf;
    rd_kafka_topic_conf_t       *topic_conf;

    if (ctx->kafka != NULL && ctx->topic != NULL)
        return(0);

    if (ctx->kafka == NULL) {
        if ((conf = rd_kafka_conf_dup(ctx->kafka_conf)) == NULL) {
            ERROR("write_kafka plugin: cannot duplicate kafka config");
            return(1);
        }

        if ((ctx->kafka = rd_kafka_new(RD_KAFKA_PRODUCER, conf,
                                    errbuf, sizeof(errbuf))) == NULL) {
            ERROR("write_kafka plugin: cannot create kafka handle.");
            return 1;
        }

        rd_kafka_conf_destroy(ctx->kafka_conf);
        ctx->kafka_conf = NULL;

        INFO ("write_kafka plugin: created KAFKA handle : %s", rd_kafka_name(ctx->kafka));

#if defined(HAVE_LIBRDKAFKA_LOGGER) && !defined(HAVE_LIBRDKAFKA_LOG_CB)
        rd_kafka_set_logger(ctx->kafka, kafka_log);
#endif
    }

    if (ctx->topic == NULL ) {
        if ((topic_conf = rd_kafka_topic_conf_dup(ctx->conf)) == NULL) {
            ERROR("write_kafka plugin: cannot duplicate kafka topic config");
            return 1;
        }

        if ((ctx->topic = rd_kafka_topic_new(ctx->kafka, ctx->topic_name,
                                            topic_conf)) == NULL) {
            ERROR("write_kafka plugin: cannot create topic : %s\n",
            rd_kafka_err2str(rd_kafka_errno2err(errno)));
            return errno;
        }

        rd_kafka_topic_conf_destroy(ctx->conf);
        ctx->conf = NULL;

        INFO ("write_kafka plugin: handle created for topic : %s", rd_kafka_topic_name(ctx->topic));
    }

    return(0);

}