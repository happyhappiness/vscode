   if (download->is_hash_checking() || download->is_active())
     throw torrent::internal_error("DownloadList::hash_done(...) download in invalid state.");
 
   if (!download->is_hash_checked()) {
     download->set_hash_failed(true);
     
-    rpc::commands.call_catch("event.download.hash_done", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
+    rpc::commands.call_catch("event.download.hash_failed", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
     return;
   }
 
   // Need to find some sane conditional here. Can we check the total
   // downloaded to ensure something was transferred, thus we didn't
   // just hash an already completed torrent with lacking session data?
   //
   // Perhaps we should use a seperate variable or state, and check
   // that. Thus we can bork the download if the hash check doesn't
   // confirm all the data, avoiding large BW usage on f.ex. the
   // ReiserFS bug with >4GB files.
 
-  int64_t hashing = rpc::call_command_value("d.get_hashing", rpc::make_target(download));
-  rpc::call_command_set_value("d.set_hashing", Download::variable_hashing_stopped, rpc::make_target(download));
+  int64_t hashing = rpc::call_command_value("d.hashing", rpc::make_target(download));
+  rpc::call_command_set_value("d.hashing.set", Download::variable_hashing_stopped, rpc::make_target(download));
+
+  if (download->is_done() && download->download()->info()->is_meta_download())
+    return process_meta_download(download);
 
   switch (hashing) {
   case Download::variable_hashing_initial:
   case Download::variable_hashing_rehash:
     // Normal re/hashing.
 
     // If the download was previously completed but the files were
     // f.ex deleted, then we clear the state and complete.
-    if (rpc::call_command_value("d.get_complete", rpc::make_target(download)) && !download->is_done()) {
-      rpc::call_command("d.set_state", (int64_t)0, rpc::make_target(download));
+    if (rpc::call_command_value("d.complete", rpc::make_target(download)) && !download->is_done()) {
+      rpc::call_command("d.state.set", (int64_t)0, rpc::make_target(download));
       download->set_message("Download registered as completed, but hash check returned unfinished chunks.");
     }
 
     // Save resume data so we update time-stamps and priorities if
     // they were invalid/changed while loading/hashing.
-    rpc::call_command("d.set_complete", (int64_t)download->is_done(), rpc::make_target(download));
+    rpc::call_command("d.complete.set", (int64_t)download->is_done(), rpc::make_target(download));
     torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));
 
-    if (rpc::call_command_value("d.get_state", rpc::make_target(download)) == 1)
+    if (rpc::call_command_value("d.state", rpc::make_target(download)) == 1)
       resume(download, download->resume_flags());
     //rpc::commands.call_catch("scheduler.simple.resume", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
 
     break;
 
   case Download::variable_hashing_last:
 
     if (download->is_done()) {
       confirm_finished(download);
     } else {
       download->set_message("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
       control->core()->push_log("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
+      rpc::commands.call_catch("event.download.hash_final_failed", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
     }
     
     break;
 
   case Download::variable_hashing_stopped:
   default:
