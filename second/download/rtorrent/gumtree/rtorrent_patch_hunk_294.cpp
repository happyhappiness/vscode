     control->core()->push_log_std("Could not unlink tied file: " + std::string(rak::error_number::current().c_str()));
 
   rpc::call_command("d.tied_to_file.set", std::string(), rpc::make_target(download));
   return torrent::Object();
 }
 
-torrent::Object
-apply_d_connection_type(core::Download* download, const std::string& name) {
-  torrent::Download::ConnectionType connType;
-
-  if (name == "leech")
-    connType = torrent::Download::CONNECTION_LEECH;
-  else if (name == "seed")
-    connType = torrent::Download::CONNECTION_SEED;
-  else if (name == "initial_seed")
-    connType = torrent::Download::CONNECTION_INITIAL_SEED;
-  else
-    throw torrent::input_error("Unknown peer connection type selected.");
-
-  download->download()->set_connection_type(connType);
-  return torrent::Object();
-}
-
 void
 apply_d_directory(core::Download* download, const std::string& name) {
   if (!download->file_list()->is_multi_file())
     download->set_root_directory(name);
   else if (name.empty() || *name.rbegin() == '/')
     download->set_root_directory(name + download->info()->name());
   else
     download->set_root_directory(name + "/" + download->info()->name());
 }
 
-const char*
-retrieve_d_connection_type(core::Download* download) {
-  switch (download->download()->connection_type()) {
-  case torrent::Download::CONNECTION_LEECH:
-    return "leech";
-  case torrent::Download::CONNECTION_SEED:
-    return "seed";
-  case torrent::Download::CONNECTION_INITIAL_SEED:
-    return "initial_seed";
-  default:
-    return "unknown";
-  }
+torrent::Object
+apply_d_connection_type(core::Download* download, const std::string& name) {
+  torrent::Download::ConnectionType t =
+    (torrent::Download::ConnectionType)torrent::option_find_string(torrent::OPTION_CONNECTION_TYPE, name.c_str());
+
+  download->download()->set_connection_type(t);
+  return torrent::Object();
+}
+
+torrent::Object
+apply_d_choke_heuristics(core::Download* download, const std::string& name, bool is_down) {
+  torrent::Download::HeuristicType t =
+    (torrent::Download::HeuristicType)torrent::option_find_string(torrent::OPTION_CHOKE_HEURISTICS, name.c_str());
+
+  if (is_down)
+    download->download()->set_download_choke_heuristic(t);
+  else
+    download->download()->set_upload_choke_heuristic(t);
+
+  return torrent::Object();
 }
 
 const char*
 retrieve_d_priority_str(core::Download* download) {
   switch (download->priority()) {
   case 0:
