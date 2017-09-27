     *inuse = 1;
     *id = i;
     (*slot->num_free)--;
     return APR_SUCCESS;
 }
 
+static apr_status_t slotmem_fgrab(ap_slotmem_instance_t *slot, unsigned int id)
+{
+    char *inuse;
+    
+    if (!slot) {
+        return APR_ENOSHMAVAIL;
+    }
+
+    if (id >= slot->desc.num) {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02236)
+                     "slotmem(%s) fgrab failed. Num %u/num_free %u",
+                     slot->name, slotmem_num_slots(slot),
+                     slotmem_num_free_slots(slot));
+        return APR_EINVAL;
+    }
+    inuse = slot->inuse + id;
+
+    if (!*inuse) {
+        *inuse = 1;
+        (*slot->num_free)--;
+    }
+    return APR_SUCCESS;
+}
+
 static apr_status_t slotmem_release(ap_slotmem_instance_t *slot,
                                     unsigned int id)
 {
     char *inuse;
 
     if (!slot) {
