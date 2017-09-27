         rv = APR_EGENERAL;
     }
 
     return rv;
 }
 
-AP_DECLARE(apr_status_t) ap_mpm_note_child_killed(int childnum)
+static void end_gen(mpm_gen_info_t *gi)
+{
+    ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, ap_server_conf,
+                 "end of generation %d", gi->gen);
+    ap_run_end_generation(ap_server_conf, gi->gen);
+    APR_RING_REMOVE(gi, link);
+    APR_RING_INSERT_HEAD(unused_geninfo, gi, mpm_gen_info_t, link);
+}
+
+apr_status_t ap_mpm_end_gen_helper(void *unused) /* cleanup on pconf */
 {
-    return ap_run_mpm_note_child_killed(childnum);
+    int gen = ap_config_generation - 1; /* differs from MPM generation */
+    mpm_gen_info_t *cur;
+
+    if (geninfo == NULL) {
+        /* initial pconf teardown, MPM hasn't run */
+        return APR_SUCCESS;
+    }
+
+    cur = APR_RING_FIRST(geninfo);
+    while (cur != APR_RING_SENTINEL(geninfo, mpm_gen_info_t, link) &&
+           cur->gen != gen) {
+        cur = APR_RING_NEXT(cur, link);
+    }
+
+    if (cur == APR_RING_SENTINEL(geninfo, mpm_gen_info_t, link)) {
+        /* last child of generation already exited */
+        ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, ap_server_conf,
+                     "no record of generation %d", gen);
+    }
+    else {
+        cur->done = 1;
+        if (cur->active == 0) {
+            end_gen(cur);
+        }
+    }
+
+    return APR_SUCCESS;
+}
+
+/* core's child-status hook
+ * tracks number of remaining children per generation and
+ * runs the end-generation hook when the last child of
+ * a generation exits
+ */
+void ap_core_child_status(server_rec *s, pid_t pid,
+                          ap_generation_t gen, int slot,
+                          mpm_child_status status)
+{
+    mpm_gen_info_t *cur;
+    const char *status_msg = "unknown status";
+
+    if (!gen_head_init) { /* where to run this? */
+        gen_head_init = 1;
+        geninfo = apr_pcalloc(s->process->pool, sizeof *geninfo);
+        unused_geninfo = apr_pcalloc(s->process->pool, sizeof *unused_geninfo);
+        APR_RING_INIT(geninfo, mpm_gen_info_t, link);
+        APR_RING_INIT(unused_geninfo, mpm_gen_info_t, link);
+    }
+
+    cur = APR_RING_FIRST(geninfo);
+    while (cur != APR_RING_SENTINEL(geninfo, mpm_gen_info_t, link) &&
+           cur->gen != gen) {
+        cur = APR_RING_NEXT(cur, link);
+    }
+
+    switch(status) {
+    case MPM_CHILD_STARTED:
+        status_msg = "started";
+        if (cur == APR_RING_SENTINEL(geninfo, mpm_gen_info_t, link)) {
+            /* first child for this generation */
+            if (!APR_RING_EMPTY(unused_geninfo, mpm_gen_info_t, link)) {
+                cur = APR_RING_FIRST(unused_geninfo);
+                APR_RING_REMOVE(cur, link);
+                cur->active = cur->done = 0;
+            }
+            else {
+                cur = apr_pcalloc(s->process->pool, sizeof *cur);
+            }
+            cur->gen = gen;
+            APR_RING_ELEM_INIT(cur, link);
+            APR_RING_INSERT_HEAD(geninfo, cur, mpm_gen_info_t, link);
+        }
+        ap_random_parent_after_fork();
+        ++cur->active;
+        break;
+    case MPM_CHILD_EXITED:
+        status_msg = "exited";
+        if (cur == APR_RING_SENTINEL(geninfo, mpm_gen_info_t, link)) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00546)
+                         "no record of generation %d of exiting child %" APR_PID_T_FMT,
+                         gen, pid);
+        }
+        else {
+            --cur->active;
+            if (!cur->active && cur->done) { /* no children, server has stopped/restarted */
+                end_gen(cur);
+            }
+        }
+        break;
+    case MPM_CHILD_LOST_SLOT:
+        status_msg = "lost slot";
+        /* we don't track by slot, so it doesn't matter */
+        break;
+    }
+    ap_log_error(APLOG_MARK, APLOG_TRACE4, 0, s,
+                 "mpm child %" APR_PID_T_FMT " (gen %d/slot %d) %s",
+                 pid, gen, slot, status_msg);
 }
 
 AP_DECLARE(apr_status_t) ap_mpm_register_timed_callback(apr_time_t t, ap_mpm_callback_fn_t *cbfn, void *baton)
 {
     return ap_run_mpm_register_timed_callback(t, cbfn, baton);
 }
