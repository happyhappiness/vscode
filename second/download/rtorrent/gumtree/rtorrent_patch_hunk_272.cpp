   default:
     // Either an error or someone wrote to the hashing variable...
     download->set_message("Hash check completed but the \"hashing\" variable is in an invalid state.");
     return;
   }
 
-  std::for_each(slot_map_hash_done().begin(), slot_map_hash_done().end(), download_list_call(download));
+  rpc::commands.call_catch("event.download.hash_done", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
 }
 
 void
 DownloadList::hash_queue(Download* download, int type) {
   check_contains(download);
 
