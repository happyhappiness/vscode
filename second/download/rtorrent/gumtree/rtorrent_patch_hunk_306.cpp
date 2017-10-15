     first = print_buffer(first, last, "Inactive: ");
 
   if (d->is_hash_checking()) {
     first = print_buffer(first, last, "Checking hash [%2i%%]",
                          (d->download()->chunks_hashed() * 100) / d->download()->file_list()->size_chunks());
 
-  } else if (d->tracker_list()->has_active() && d->tracker_list()->focus() < d->tracker_list()->end()) {
-    torrent::TrackerList* tl = d->tracker_list();
+  } else if (d->tracker_list()->has_active()) {
+    torrent::TrackerList::iterator itr =
+      std::find_if(d->tracker_list()->begin(), d->tracker_list()->end(),
+                   std::mem_fun(&torrent::Tracker::is_busy));
     char status[128];
 
-    (*tl->focus())->get_status(status, sizeof(status));
+    (*itr)->get_status(status, sizeof(status));
     first = print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s %s",
-                         (*tl->focus())->group(), tl->focus_index(), (*tl->focus())->url().c_str(), status);
+                         (*itr)->group(), std::distance(d->tracker_list()->begin(), itr), (*itr)->url().c_str(), status);
 
   } else if (!d->message().empty()) {
     first = print_buffer(first, last, "%s", d->message().c_str());
 
   } else {
     *first = '\0';
