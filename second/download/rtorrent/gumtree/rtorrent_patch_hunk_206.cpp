 
 namespace core {
   extern void
   path_expand(std::vector<std::string>* paths, const std::string& pattern);
 }
 
+// void
+// apply_new_string(const std::string& args) {
+//   std::string::const_iterator split = std::find(args.begin(), args.end(), ',');
+
+//   std::string key = 
+
+//   if (control->variable()->has(args))
+
+//   variables->insert("tracker_dump",          new utils::VariableAny(std::string()));
+// }
+
 void
-apply_hash_read_ahead(__UNUSED Control* m, int arg) {
+apply_hash_read_ahead(int arg) {
   torrent::set_hash_read_ahead(arg << 20);
 }
 
 void
-apply_hash_interval(__UNUSED Control* m, int arg) {
+apply_hash_interval(int arg) {
   torrent::set_hash_interval(arg * 1000);
 }
 
 // The arg string *must* have been checked with validate_port_range
 // first.
 void
-apply_port_range(Control* m, const std::string& arg) {
+apply_port_range(const std::string& arg) {
   int a = 0, b = 0;
     
   std::sscanf(arg.c_str(), "%i-%i", &a, &b);
 
-  m->core()->set_port_range(a, b);
+  control->core()->set_port_range(a, b);
 }
 
 void
-apply_load(Control* m, const std::string& arg) {
-  m->core()->try_create_download_expand(arg, false, false, true);
+apply_load(const std::string& arg) {
+  control->core()->try_create_download_expand(arg, false, false, true);
 }
 
 void
-apply_load_verbose(Control* m, const std::string& arg) {
-  m->core()->try_create_download_expand(arg, false, true, true);
+apply_load_verbose(const std::string& arg) {
+  control->core()->try_create_download_expand(arg, false, true, true);
 }
 
 void
-apply_load_start(Control* m, const std::string& arg) {
-  m->core()->try_create_download_expand(arg, true, false, true);
+apply_load_start(const std::string& arg) {
+  control->core()->try_create_download_expand(arg, true, false, true);
 }
 
 void
-apply_load_start_verbose(Control* m, const std::string& arg) {
-  m->core()->try_create_download_expand(arg, true, true, true);
+apply_load_start_verbose(const std::string& arg) {
+  control->core()->try_create_download_expand(arg, true, true, true);
 }
 
 void
-apply_start_tied(Control* m) {
-  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ++itr) {
-    if ((*itr)->variable_value("state") == 1)
+apply_start_tied() {
+  for (core::DownloadList::iterator itr = control->core()->download_list()->begin(); itr != control->core()->download_list()->end(); ++itr) {
+    if ((*itr)->get_value("state") == 1)
       continue;
 
     rak::file_stat fs;
-    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
+    const std::string& tiedToFile = (*itr)->get_string("tied_to_file");
 
     if (!tiedToFile.empty() && fs.update(rak::path_expand(tiedToFile)))
-      m->core()->download_list()->start_try(*itr);
+      control->core()->download_list()->start_try(*itr);
   }
 }
 
 void
-apply_stop_untied(Control* m) {
-  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ++itr) {
-    if ((*itr)->variable_value("state") == 0)
+apply_stop_untied() {
+  for (core::DownloadList::iterator itr = control->core()->download_list()->begin(); itr != control->core()->download_list()->end(); ++itr) {
+    if ((*itr)->get_value("state") == 0)
       continue;
 
     rak::file_stat fs;
-    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
+    const std::string& tiedToFile = (*itr)->get_string("tied_to_file");
 
     if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)))
-      m->core()->download_list()->stop_try(*itr);
+      control->core()->download_list()->stop_try(*itr);
   }
 }
 
 void
-apply_close_untied(Control* m) {
-  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ++itr) {
+apply_close_untied() {
+  for (core::DownloadList::iterator itr = control->core()->download_list()->begin(); itr != control->core()->download_list()->end(); ++itr) {
     rak::file_stat fs;
-    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
+    const std::string& tiedToFile = (*itr)->get_string("tied_to_file");
 
-    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)) && m->core()->download_list()->stop_try(*itr))
-      m->core()->download_list()->close(*itr);
+    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)) && control->core()->download_list()->stop_try(*itr))
+      control->core()->download_list()->close(*itr);
   }
 }
 
 void
-apply_remove_untied(Control* m) {
-  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ) {
+apply_remove_untied() {
+  for (core::DownloadList::iterator itr = control->core()->download_list()->begin(); itr != control->core()->download_list()->end(); ) {
     rak::file_stat fs;
-    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
+    const std::string& tiedToFile = (*itr)->get_string("tied_to_file");
 
-    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)) && m->core()->download_list()->stop_try(*itr))
-      itr = m->core()->download_list()->erase(itr);
+    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)) && control->core()->download_list()->stop_try(*itr))
+      itr = control->core()->download_list()->erase(itr);
     else
       ++itr;
   }
 }
 
 void
-apply_close_low_diskspace(Control* m, int64_t arg) {
-  core::Manager::DListItr itr = m->core()->download_list()->begin();
+apply_close_low_diskspace(int64_t arg) {
+  core::Manager::DListItr itr = control->core()->download_list()->begin();
 
-  while ((itr = std::find_if(itr, m->core()->download_list()->end(), std::mem_fun(&core::Download::is_downloading))) != m->core()->download_list()->end()) {
+  while ((itr = std::find_if(itr, control->core()->download_list()->end(), std::mem_fun(&core::Download::is_downloading))) != control->core()->download_list()->end()) {
     if ((*itr)->file_list()->free_diskspace() < (uint64_t)arg) {
-      m->core()->download_list()->close(*itr);
+      control->core()->download_list()->close(*itr);
 
       (*itr)->set_hash_failed(true);
       (*itr)->set_message(std::string("Low diskspace."));
     }
 
     ++itr;
   }
 }
 
 void
-apply_stop_on_ratio(Control* m, const std::string& arg) {
+apply_stop_on_ratio(const std::string& arg) {
   int64_t minRatio = 0;  // first argument:  minimum ratio to reach
   int64_t minUpload = 0; // second argument: minimum upload amount to reach [optional]
   int64_t maxRatio = 0;  // third argument:  maximum ratio to reach [optional]
 
   rak::split_iterator_t<std::string> sitr = rak::split_iterator(arg, ',');
 
