     }
 
     debugs(90, 3, "quick-abort? YES default");
     return true;
 }
 
-/// Aborts a swapping-out entry if nobody needs it any more _and_
-/// continuing swap out is not reasonable per CheckQuickAbortIsReasonable().
-static void
-CheckQuickAbort(StoreEntry * entry)
-{
-    assert (entry);
-
-    if (storePendingNClients(entry) > 0)
-        return;
-
-    if (!shutting_down && Store::Root().transientReaders(*entry))
-        return;
-
-    if (entry->store_status != STORE_PENDING)
-        return;
-
-    if (EBIT_TEST(entry->flags, ENTRY_SPECIAL))
-        return;
-
-    if (!CheckQuickAbortIsReasonable(entry))
-        return;
-
-    entry->abort();
-}
-
 void
 store_client::dumpStats(MemBuf * output, int clientNumber) const
 {
     if (_callback.pending())
         return;
 
-    output->Printf("\tClient #%d, %p\n", clientNumber, _callback.callback_data);
-
-    output->Printf("\t\tcopy_offset: %" PRId64 "\n",
-                   copyInto.offset);
-
-    output->Printf("\t\tcopy_size: %d\n",
-                   (int) copyInto.length);
-
-    output->Printf("\t\tflags:");
+    output->appendf("\tClient #%d, %p\n", clientNumber, _callback.callback_data);
+    output->appendf("\t\tcopy_offset: %" PRId64 "\n", copyInto.offset);
+    output->appendf("\t\tcopy_size: %" PRIuSIZE "\n", copyInto.length);
+    output->append("\t\tflags:", 8);
 
     if (flags.disk_io_pending)
-        output->Printf(" disk_io_pending");
+        output->append(" disk_io_pending", 16);
 
     if (flags.store_copying)
-        output->Printf(" store_copying");
+        output->append(" store_copying", 14);
 
     if (flags.copy_event_pending)
-        output->Printf(" copy_event_pending");
+        output->append(" copy_event_pending", 19);
 
-    output->Printf("\n");
+    output->append("\n",1);
 }
 
 bool
 store_client::Callback::pending() const
 {
     return callback_handler && callback_data;
