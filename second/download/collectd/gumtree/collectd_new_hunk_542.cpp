
static int kafka_handle(struct kafka_topic_context *);
static int kafka_write(const data_set_t *, const value_list_t *, user_data_t *);
static int32_t kafka_partition(const rd_kafka_topic_t *, const void *, size_t,
                               int32_t, void *, void *);

/* Version 0.9.0 of librdkafka deprecates rd_kafka_set_logger() in favor of
 * rd_kafka_conf_set_log_cb(). This is to make sure we're not using the
 * deprecated function. */
#ifdef HAVE_LIBRDKAFKA_LOG_CB
# undef HAVE_LIBRDKAFKA_LOGGER
#endif

#if defined(HAVE_LIBRDKAFKA_LOGGER) || defined(HAVE_LIBRDKAFKA_LOG_CB)
static void kafka_log(const rd_kafka_t *, int, const char *, const char *);

static void kafka_log(const rd_kafka_t *rkt, int level,
                      const char *fac, const char *msg)
{
    plugin_log(level, "%s", msg);
