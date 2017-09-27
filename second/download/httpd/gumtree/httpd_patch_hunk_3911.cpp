 {
     h2_task_input *input = (h2_task_input*)ctx;
     apr_brigade_printf(input->bb, NULL, NULL, "%s: %s\r\n", name, value);
     return 1;
 }
 
-h2_task_input *h2_task_input_create(h2_task_env *env, apr_pool_t *pool, 
+h2_task_input *h2_task_input_create(h2_task *task, apr_pool_t *pool, 
                                     apr_bucket_alloc_t *bucket_alloc)
 {
     h2_task_input *input = apr_pcalloc(pool, sizeof(h2_task_input));
     if (input) {
-        input->env = env;
+        input->task = task;
         input->bb = NULL;
         
-        if (env->serialize_headers) {
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, &env->c,
+        if (task->serialize_headers) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
                           "h2_task_input(%s): serialize request %s %s", 
-                          env->id, env->method, env->path);
+                          task->id, task->request->method, task->request->path);
             input->bb = apr_brigade_create(pool, bucket_alloc);
             apr_brigade_printf(input->bb, NULL, NULL, "%s %s HTTP/1.1\r\n", 
-                               env->method, env->path);
-            apr_table_do(ser_header, input, env->headers, NULL);
+                               task->request->method, task->request->path);
+            apr_table_do(ser_header, input, task->request->headers, NULL);
             apr_brigade_puts(input->bb, NULL, NULL, "\r\n");
-            if (input->env->input_eos) {
+            if (input->task->input_eos) {
                 APR_BRIGADE_INSERT_TAIL(input->bb, apr_bucket_eos_create(bucket_alloc));
             }
         }
-        else if (!input->env->input_eos) {
+        else if (!input->task->input_eos) {
             input->bb = apr_brigade_create(pool, bucket_alloc);
         }
         else {
             /* We do not serialize and have eos already, no need to
              * create a bucket brigade. */
         }
-        
-        if (APLOGcdebug(&env->c)) {
-            char buffer[1024];
-            apr_size_t len = sizeof(buffer)-1;
-            if (input->bb) {
-                apr_brigade_flatten(input->bb, buffer, &len);
-            }
-            else {
-                len = 0;
-            }
-            buffer[len] = 0;
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, &env->c,
-                          "h2_task_input(%s): request is: %s", 
-                          env->id, buffer);
-        }
     }
     return input;
 }
 
 void h2_task_input_destroy(h2_task_input *input)
 {
