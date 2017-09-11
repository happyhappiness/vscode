#include "hiredis.h"
#include "net.h"
#include "sds.h"
#include "util.h"

typedef struct redisReader {
    struct redisReplyObjectFunctions *fn;
    sds error; /* holds optional error */
    void *reply; /* holds temporary reply */

    sds buf; /* read buffer */
    size_t pos; /* buffer cursor */
    size_t len; /* buffer length */

    redisReadTask rstack[9]; /* stack of read tasks */
    int ridx; /* index of stack */
    void *privdata; /* user-settable arbitrary field */
} redisReader;

static redisReply *createReplyObject(int type);
static void *createStringObject(const redisReadTask *task, char *str, size_t len);
static void *createArrayObject(const redisReadTask *task, int elements);
static void *createIntegerObject(const redisReadTask *task, long long value);
static void *createNilObject(const redisReadTask *task);
static void redisSetReplyReaderError(redisReader *r, sds err);

/* Default set of functions to build the reply. */
static redisReplyObjectFunctions defaultFunctions = {
    createStringObject,
    createArrayObject,
