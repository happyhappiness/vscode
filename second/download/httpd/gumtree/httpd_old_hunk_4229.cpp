#include <http_core.h>
#include <http_log.h>

#include "mod_http2.h"

#include "h2_private.h"
#include "h2_config.h"
#include "h2_conn.h"
#include "h2_ctx.h"
#include "h2_h2.h"
#include "h2_int_queue.h"
#include "h2_io.h"
#include "h2_io_set.h"
#include "h2_response.h"
#include "h2_mplx.h"
#include "h2_ngn_shed.h"
#include "h2_request.h"
#include "h2_stream.h"
#include "h2_task.h"
#include "h2_task_input.h"
#include "h2_task_output.h"
#include "h2_worker.h"
#include "h2_workers.h"
#include "h2_util.h"


#define H2_MPLX_IO_OUT(lvl,m,io,msg) \
    do { \
        if (APLOG_C_IS_LEVEL((m)->c,lvl)) \
        h2_util_bb_log((m)->c,(io)->id,lvl,msg,(io)->bbout); \
    } while(0)
    
#define H2_MPLX_IO_IN(lvl,m,io,msg) \
    do { \
        if (APLOG_C_IS_LEVEL((m)->c,lvl)) \
        h2_util_bb_log((m)->c,(io)->id,lvl,msg,(io)->bbin); \
    } while(0)


/* NULL or the mutex hold by this thread, used for recursive calls
 */
static apr_threadkey_t *thread_lock;

apr_status_t h2_mplx_child_init(apr_pool_t *pool, server_rec *s)
