 void
 apply_load(Control* m, const std::string& arg) {
   m->core()->try_create_download_expand(arg, false, false, true);
 }
 
 void
+apply_load_verbose(Control* m, const std::string& arg) {
+  m->core()->try_create_download_expand(arg, false, true, true);
+}
+
+void
 apply_load_start(Control* m, const std::string& arg) {
   m->core()->try_create_download_expand(arg, true, false, true);
 }
 
 void
-apply_stop_untied(Control* m) {
-  core::Manager::DListItr itr = m->core()->download_list()->begin();
+apply_load_start_verbose(Control* m, const std::string& arg) {
+  m->core()->try_create_download_expand(arg, true, true, true);
+}
+
+void
+apply_start_tied(Control* m) {
+  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ++itr) {
+    if ((*itr)->variable_value("state") == 1)
+      continue;
 
-  while ((itr = std::find_if(itr, m->core()->download_list()->end(),
-			     rak::on(rak::bind2nd(std::mem_fun(&core::Download::variable_string), "tied_to_file"),
-				     std::not1(std::mem_fun_ref(&std::string::empty)))))
-	 != m->core()->download_list()->end()) {
     rak::file_stat fs;
+    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
 
-    if (!fs.update(rak::path_expand((*itr)->variable_string("tied_to_file")))) {
-      (*itr)->variable()->set("tied_to_file", std::string());
-      m->core()->download_list()->stop(*itr);
-    }
+    if (!tiedToFile.empty() && fs.update(rak::path_expand(tiedToFile)))
+      m->core()->download_list()->start_try(*itr);
+  }
+}
 
-    ++itr;
+void
+apply_stop_untied(Control* m) {
+  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ++itr) {
+    if ((*itr)->variable_value("state") == 0)
+      continue;
+
+    rak::file_stat fs;
+    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
+
+    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)))
+      m->core()->download_list()->stop_try(*itr);
   }
 }
 
 void
 apply_close_untied(Control* m) {
-  core::Manager::DListItr itr = m->core()->download_list()->begin();
+  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ++itr) {
+    rak::file_stat fs;
+    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
 
-  while ((itr = std::find_if(itr, m->core()->download_list()->end(),
-			     rak::on(rak::bind2nd(std::mem_fun(&core::Download::variable_string), "tied_to_file"),
-				     std::not1(std::mem_fun_ref(&std::string::empty)))))
-	 != m->core()->download_list()->end()) {
+    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)) && m->core()->download_list()->stop_try(*itr))
+      m->core()->download_list()->close(*itr);
+  }
+}
+
+void
+apply_remove_untied(Control* m) {
+  for (core::DownloadList::iterator itr = m->core()->download_list()->begin(); itr != m->core()->download_list()->end(); ) {
     rak::file_stat fs;
+    const std::string& tiedToFile = (*itr)->variable_string("tied_to_file");
 
-    if (!fs.update(rak::path_expand((*itr)->variable_string("tied_to_file")))) {
-      (*itr)->variable()->set("tied_to_file", std::string());
+    if (!tiedToFile.empty() && !fs.update(rak::path_expand(tiedToFile)) && m->core()->download_list()->stop_try(*itr))
+      itr = m->core()->download_list()->erase(itr);
+    else
+      ++itr;
+  }
+}
+
+void
+apply_close_low_diskspace(Control* m, int64_t arg) {
+  core::Manager::DListItr itr = m->core()->download_list()->begin();
+
+  while ((itr = std::find_if(itr, m->core()->download_list()->end(), std::mem_fun(&core::Download::is_downloading))) != m->core()->download_list()->end()) {
+    rak::fs_stat stat;
+    std::string path = (*itr)->file_list()->root_dir() + (*itr)->file_list()->get(0).path()->as_string();
+
+    if (!stat.update(path)) {
+      m->core()->push_log(std::string("Cannot read free diskspace: ") + strerror(errno) + " for " + path);
+
+    } else if (stat.bytes_avail() < arg) {
       m->core()->download_list()->close(*itr);
+
+      (*itr)->set_hash_failed(true);
+      (*itr)->set_message(std::string("Low diskspace"));
     }
 
     ++itr;
   }
 }
 
 void
-apply_remove_untied(Control* m) {
+apply_stop_on_ratio(Control* m, const std::string& arg) {
+  int64_t minRatio = 0;  // first argument:  minimum ratio to reach
+  int64_t minUpload = 0; // second argument: minimum upload amount to reach [optional]
+  int64_t maxRatio = 0;  // third argument:  maximum ratio to reach [optional]
+
+  rak::split_iterator_t<std::string> sitr = rak::split_iterator(arg, ',');
+
+  utils::Variable::string_to_value_unit(rak::trim(*sitr).c_str(), &minRatio, 0, 1);
+
+  if (++sitr != rak::split_iterator(arg))
+    utils::Variable::string_to_value_unit(rak::trim(*sitr).c_str(), &minUpload, 0, 1);
+
+  if (++sitr != rak::split_iterator(arg))
+    utils::Variable::string_to_value_unit(rak::trim(*sitr).c_str(), &maxRatio, 0, 1);
+
   core::Manager::DListItr itr = m->core()->download_list()->begin();
 
-  while ((itr = std::find_if(itr, m->core()->download_list()->end(),
-			     rak::on(rak::bind2nd(std::mem_fun(&core::Download::variable_string), "tied_to_file"),
-				     std::not1(std::mem_fun_ref(&std::string::empty)))))
-	 != m->core()->download_list()->end()) {
-    rak::file_stat fs;
+  while ((itr = std::find_if(itr, m->core()->download_list()->end(), std::mem_fun(&core::Download::is_seeding))) != m->core()->download_list()->end()) {
+    int64_t totalUpload = (*itr)->download()->up_rate()->total();
+    int64_t totalDone = (*itr)->download()->bytes_done();
 
-    if (!fs.update(rak::path_expand((*itr)->variable_string("tied_to_file")))) {
-      (*itr)->variable()->set("tied_to_file", std::string());
-      m->core()->download_list()->stop(*itr);
-      itr = m->core()->download_list()->erase(itr);
+    if ((totalUpload >= minUpload && totalUpload * 100 >= totalDone * minRatio) || (maxRatio > 0 && totalUpload * 100 > totalDone * maxRatio))
+        m->core()->download_list()->stop_try(*itr);
 
-    } else {
-      ++itr;
-    }
+    ++itr;
   }
 }
 
 void
 apply_encoding_list(__UNUSED Control* m, const std::string& arg) {
   torrent::encoding_list()->push_back(arg);
