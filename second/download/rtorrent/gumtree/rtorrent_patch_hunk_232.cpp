   //
   // Perhaps we should use a seperate variable or state, and check
   // that. Thus we can bork the download if the hash check doesn't
   // confirm all the data, avoiding large BW usage on f.ex. the
   // ReiserFS bug with >4GB files.
 
-  int64_t hashing = rpc::call_command_d_value("d.get_hashing", download);
-  rpc::call_command_d_set_value("d.set_hashing", download, Download::variable_hashing_stopped);
+  int64_t hashing = rpc::call_command_value("d.get_hashing", rpc::make_target(download));
+  rpc::call_command_set_value("d.set_hashing", Download::variable_hashing_stopped, rpc::make_target(download));
 
   switch (hashing) {
   case Download::variable_hashing_initial:
   case Download::variable_hashing_rehash:
     // Normal re/hashing.
 
     // If the download was previously completed but the files were
     // f.ex deleted, then we clear the state and complete.
-    if (rpc::call_command_d_value("d.get_complete", download) && !download->is_done()) {
-      rpc::call_command_d("d.set_state", download, (int64_t)0);
+    if (rpc::call_command_value("d.get_complete", rpc::make_target(download)) && !download->is_done()) {
+      rpc::call_command("d.set_state", (int64_t)0, rpc::make_target(download));
       download->set_message("Download registered as completed, but hash check returned unfinished chunks.");
     }
 
     // Save resume data so we update time-stamps and priorities if
     // they were invalid/changed while loading/hashing.
-    rpc::call_command_d("d.set_complete", download, (int64_t)download->is_done());
+    rpc::call_command("d.set_complete", (int64_t)download->is_done(), rpc::make_target(download));
     torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));
 
-    if (rpc::call_command_d_value("d.get_state", download) == 1)
+    if (rpc::call_command_value("d.get_state", rpc::make_target(download)) == 1)
       resume(download);
 
     break;
 
   case Download::variable_hashing_last:
 
