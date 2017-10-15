     first = print_buffer(first, last, "Inactive: ");
 
   if (d->is_hash_checking()) {
     first = print_buffer(first, last, "Checking hash [%2i%%]",
                          (d->download()->chunks_hashed() * 100) / d->download()->file_list()->size_chunks());
 
-  } else if (d->tracker_list()->has_active()) {
+  } else if (d->tracker_list()->has_active_not_scrape()) {
     torrent::TrackerList::iterator itr =
       std::find_if(d->tracker_list()->begin(), d->tracker_list()->end(),
-                   std::mem_fun(&torrent::Tracker::is_busy));
+                   std::mem_fun(&torrent::Tracker::is_busy_not_scrape));
     char status[128];
 
     (*itr)->get_status(status, sizeof(status));
     first = print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s %s",
                          (*itr)->group(), std::distance(d->tracker_list()->begin(), itr), (*itr)->url().c_str(), status);
 
