static void kafka_log(const rd_kafka_t *rkt, int level,
                      const char *fac, const char *msg)
{
    plugin_log(level, "%s", msg);
}