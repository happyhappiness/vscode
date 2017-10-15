       confirm_finished(download);
     } else {
       download->set_message("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
       control->core()->push_log("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
       rpc::commands.call_catch("event.download.hash_final_failed", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
     }
-    
-    break;
+
+    // TODO: Should we skip the 'hash_done' event here?
+    return;
 
   case Download::variable_hashing_stopped:
   default:
     // Either an error or someone wrote to the hashing variable...
     download->set_message("Hash check completed but the \"hashing\" variable is in an invalid state.");
     return;
