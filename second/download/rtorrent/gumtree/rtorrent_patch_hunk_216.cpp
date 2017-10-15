 
   control->command_scheduler()->parse(arg1, arg2, arg3, rpc::convert_list_to_command(itr, args.end()));
 
   return torrent::Object();
 }
 
-void apply_load(const std::string& arg)               { control->core()->try_create_download_expand(arg, false, false, true); }
-void apply_load_verbose(const std::string& arg)       { control->core()->try_create_download_expand(arg, false, true, true); }
-void apply_load_start(const std::string& arg)         { control->core()->try_create_download_expand(arg, true, false, true); }
-void apply_load_start_verbose(const std::string& arg) { control->core()->try_create_download_expand(arg, true, true, true); }
+torrent::Object
+apply_load(int flags, const torrent::Object& rawArgs) {
+  const torrent::Object::list_type&          args    = rawArgs.as_list();
+  torrent::Object::list_type::const_iterator argsItr = args.begin();
+
+  if (argsItr == args.end())
+    throw torrent::input_error("Too few arguments.");
+
+  const std::string& filename = argsItr->as_string();
+  core::Manager::command_list_type commands;
+
+  while (++argsItr != args.end())
+    commands.push_back(argsItr->as_string());
+
+  control->core()->try_create_download_expand(filename, flags, commands);
+
+  return torrent::Object();
+}
 
 void apply_import(const std::string& path)     { if (!rpc::parse_command_file(path)) throw torrent::input_error("Could not open option file: " + path); }
-void apply_try_import(const std::string& path) { if (!rpc::parse_command_file(path)) control->core()->push_log("Could not read resource file: " + path); }
+void apply_try_import(const std::string& path) { if (!rpc::parse_command_file(path)) control->core()->push_log_std("Could not read resource file: " + path); }
 
 void
 apply_close_low_diskspace(int64_t arg) {
-  core::Manager::DListItr itr = control->core()->download_list()->begin();
+  core::DownloadList* downloadList = control->core()->download_list();
+
+  core::Manager::DListItr itr = downloadList->begin();
 
-  while ((itr = std::find_if(itr, control->core()->download_list()->end(), std::mem_fun(&core::Download::is_downloading))) != control->core()->download_list()->end()) {
+  while ((itr = std::find_if(itr, downloadList->end(), std::mem_fun(&core::Download::is_downloading)))
+         != downloadList->end()) {
     if ((*itr)->file_list()->free_diskspace() < (uint64_t)arg) {
-      control->core()->download_list()->close(*itr);
+      downloadList->close(*itr);
 
       (*itr)->set_hash_failed(true);
       (*itr)->set_message(std::string("Low diskspace."));
     }
 
     ++itr;
   }
 }
 
 torrent::Object
 apply_download_list(const torrent::Object& rawArgs) {
-  const torrent::Object::list_type& args = rawArgs.as_list();
+  const torrent::Object::list_type&          args    = rawArgs.as_list();
   torrent::Object::list_type::const_iterator argsItr = args.begin();
 
   core::ViewManager* viewManager = control->view_manager();
   core::ViewManager::iterator viewItr;
 
-  if (argsItr != args.end() && !(argsItr++)->as_string().empty())
+  if (argsItr != args.end() && !argsItr->as_string().empty())
     viewItr = viewManager->find((argsItr++)->as_string());
   else
-    viewItr = viewManager->find("main");
+    viewItr = viewManager->find("default");
 
   if (viewItr == viewManager->end())
     throw torrent::input_error("Could not find view.");
 
   torrent::Object result(torrent::Object::TYPE_LIST);
   torrent::Object::list_type& resultList = result.as_list();
