print_buffer(first, last, "Tracker[%i:%i]: Connecting to %s",
		       d->get_download().tracker(d->get_download().tracker_focus()).group(),
		       d->get_download().tracker_focus(),
		       d->get_download().tracker(d->get_download().tracker_focus()).url().c_str());