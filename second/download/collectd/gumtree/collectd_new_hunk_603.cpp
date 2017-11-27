 */

#include "collectd.h"

#include "plugin.h"
#include "common.h"
#include "utils_cmd_putval.h"
#include "utils_format_graphite.h"
#include "utils_format_json.h"

#include <stdint.h>
#include <librdkafka/rdkafka.h>
#include <errno.h>

struct kafka_topic_context {
#define KAFKA_FORMAT_JSON        0
#define KAFKA_FORMAT_COMMAND     1
#define KAFKA_FORMAT_GRAPHITE    2
    uint8_t                      format;
    unsigned int                 graphite_flags;
    _Bool                        store_rates;
    rd_kafka_topic_conf_t       *conf;
    rd_kafka_topic_t            *topic;
    rd_kafka_conf_t             *kafka_conf;
    rd_kafka_t                  *kafka;
    char                        *key;
    char                        *prefix;
    char                        *postfix;
    char                         escape_char;
    char                        *topic_name;
    pthread_mutex_t              lock;
};

static int kafka_handle(struct kafka_topic_context *);
static int kafka_write(const data_set_t *, const value_list_t *, user_data_t *);
static int32_t kafka_partition(const rd_kafka_topic_t *, const void *, size_t,
                               int32_t, void *, void *);

#if defined HAVE_LIBRDKAFKA_LOGGER || defined HAVE_LIBRDKAFKA_LOG_CB
static void kafka_log(const rd_kafka_t *, int, const char *, const char *);

static void kafka_log(const rd_kafka_t *rkt, int level,
                      const char *fac, const char *msg)
{
    plugin_log(level, "%s", msg);
}
#endif

static uint32_t kafka_hash(const char *keydata, size_t keylen)
{
    uint32_t hash = 5381;
    for (; keylen > 0; keylen--)
        hash = ((hash << 5) + hash) + keydata[keylen - 1];
    return hash;
}

static int32_t kafka_partition(const rd_kafka_topic_t *rkt,
                               const void *keydata, size_t keylen,
                               int32_t partition_cnt, void *p, void *m)
{
    uint32_t key = kafka_hash(keydata, keylen);
    uint32_t target = key % partition_cnt;
    int32_t  i = partition_cnt;

    while (--i > 0 && !rd_kafka_topic_partition_available(rkt, target)) {
        target = (target + 1) % partition_cnt;
    }
    return target;
}
