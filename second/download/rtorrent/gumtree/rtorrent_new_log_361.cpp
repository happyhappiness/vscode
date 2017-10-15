print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s %s",
                         (*itr)->group(), std::distance(d->tracker_list()->begin(), itr), (*itr)->url().c_str(), status);