 #include <httpd.h>
 #include <http_core.h>
 #include <http_log.h>
 #include <http_connection.h>
 
 #include "h2_private.h"
+#include "h2_bucket_eoc.h"
 #include "h2_config.h"
 #include "h2_conn_io.h"
 #include "h2_h2.h"
 #include "h2_util.h"
 
-#define WRITE_BUFFER_SIZE     (64*1024)
+#define TLS_DATA_MAX          (16*1024) 
+
+/* Calculated like this: assuming MTU 1500 bytes
+ * 1500 - 40 (IP) - 20 (TCP) - 40 (TCP options) 
+ *      - TLS overhead (60-100) 
+ * ~= 1300 bytes */
 #define WRITE_SIZE_INITIAL    1300
-#define WRITE_SIZE_MAX        (16*1024)
-#define WRITE_SIZE_IDLE_USEC  (1*APR_USEC_PER_SEC)
-#define WRITE_SIZE_THRESHOLD  (1*1024*1024)
-
-apr_status_t h2_conn_io_init(h2_conn_io *io, conn_rec *c)
-{
-    io->connection = c;
-    io->input = apr_brigade_create(c->pool, c->bucket_alloc);
-    io->output = apr_brigade_create(c->pool, c->bucket_alloc);
-    io->buflen = 0;
-    /* That is where we start with, 
-     * see https://issues.apache.org/jira/browse/TS-2503 */
-    io->write_size = WRITE_SIZE_INITIAL; 
-    io->last_write = 0;
-    io->buffer_output = h2_h2_is_tls(c);
-
-    /* Currently we buffer only for TLS output. The reason this gives
-     * improved performance is that buckets send to the mod_ssl network
-     * filter will be encrypted in chunks. There is a special filter
-     * that tries to aggregate data, but that does not work well when
-     * bucket sizes alternate between tiny frame headers and large data
-     * chunks.
-     */
+/* Calculated like this: max TLS record size 16*1024
+ *   - 40 (IP) - 20 (TCP) - 40 (TCP options) 
+ *    - TLS overhead (60-100) 
+ * which seems to create less TCP packets overall
+ */
+#define WRITE_SIZE_MAX        (TLS_DATA_MAX - 100) 
+
+#define WRITE_BUFFER_SIZE     (8*WRITE_SIZE_MAX)
+
+apr_status_t h2_conn_io_init(h2_conn_io *io, conn_rec *c, 
+                             const h2_config *cfg, 
+                             apr_pool_t *pool)
+{
+    io->connection         = c;
+    io->input              = apr_brigade_create(pool, c->bucket_alloc);
+    io->output             = apr_brigade_create(pool, c->bucket_alloc);
+    io->buflen             = 0;
+    io->is_tls             = h2_h2_is_tls(c);
+    io->buffer_output      = io->is_tls;
+    
     if (io->buffer_output) {
         io->bufsize = WRITE_BUFFER_SIZE;
-        io->buffer = apr_pcalloc(c->pool, io->bufsize);
+        io->buffer = apr_pcalloc(pool, io->bufsize);
     }
     else {
         io->bufsize = 0;
     }
     
+    if (io->is_tls) {
+        /* That is where we start with, 
+         * see https://issues.apache.org/jira/browse/TS-2503 */
+        io->warmup_size    = h2_config_geti64(cfg, H2_CONF_TLS_WARMUP_SIZE);
+        io->cooldown_usecs = (h2_config_geti(cfg, H2_CONF_TLS_COOLDOWN_SECS) 
+                              * APR_USEC_PER_SEC);
+        io->write_size     = WRITE_SIZE_INITIAL; 
+    }
+    else {
+        io->warmup_size    = 0;
+        io->cooldown_usecs = 0;
+        io->write_size     = io->bufsize;
+    }
+
+    if (APLOGctrace1(c)) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, io->connection,
+                      "h2_conn_io(%ld): init, buffering=%d, warmup_size=%ld, cd_secs=%f",
+                      io->connection->id, io->buffer_output, (long)io->warmup_size,
+                      ((float)io->cooldown_usecs/APR_USEC_PER_SEC));
+    }
+
     return APR_SUCCESS;
 }
 
-void h2_conn_io_destroy(h2_conn_io *io)
+int h2_conn_io_is_buffered(h2_conn_io *io)
 {
-    io->input = NULL;
-    io->output = NULL;
+    return io->bufsize > 0;
 }
 
 static apr_status_t h2_conn_io_bucket_read(h2_conn_io *io,
                                            apr_read_type_e block,
                                            h2_conn_io_on_read_cb on_read_cb,
                                            void *puser, int *pdone)
