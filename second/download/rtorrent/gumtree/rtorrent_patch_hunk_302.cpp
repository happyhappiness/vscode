 
   m_download.bencode()->get_key("rtorrent").insert_key("throttle_name", throttleName);
 }
 
 void
 Download::set_root_directory(const std::string& path) {
-  torrent::FileList* fileList = m_download.file_list();
+  // If the download is open, hashed and has completed chunks make
+  // sure to verify that the download files are still present.
+  // 
+  // This should ensure that no one tries to set the destination
+  // directory 'after' moving files. In cases where the user wants to
+  // override this behavior the download must first be closed or
+  // 'd.directory_base.set' may be used.
+  rak::file_stat file_stat;
+  torrent::FileList* file_list = m_download.file_list();
+
+  if (is_hash_checked() && file_list->completed_chunks() != 0 &&
+
+      (file_list->is_multi_file() ?
+       !file_list->is_root_dir_created() :
+       !file_stat.update(file_list->front()->frozen_path()))) {
+
+    set_message("Cannot change the directory of an open download after the files have been moved.");
+    rpc::call_command("d.state.set", (int64_t)0, rpc::make_target(this));
+    control->core()->download_list()->close_directly(this);
+
+    throw torrent::input_error("Cannot change the directory of an open download atter the files have been moved.");
+  }
 
   control->core()->download_list()->close_directly(this);
-  fileList->set_root_dir(rak::path_expand(path));
+  file_list->set_root_dir(rak::path_expand(path));
 
   bencode()->get_key("rtorrent").insert_key("directory", path);
 }
 
 }
