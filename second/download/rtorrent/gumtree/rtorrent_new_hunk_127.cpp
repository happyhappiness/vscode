    *str >> *object;
    
    // Catch, delete.
    if (str->fail())
      throw torrent::input_error("Could not create download, the input is not a valid torrent.");

    download = torrent::download_add(object);

  } catch (torrent::local_error& e) {
    delete object;

    if (printLog)
      control->core()->push_log(e.what());

    return NULL;
  }

  // There's no non-critical exceptions that should be throwable by
  // the ctor, so don't catch.
  return new Download(download);
}

DownloadList::iterator
DownloadList::insert(Download* download) {
  iterator itr = base_type::insert(end(), download);

  try {
    (*itr)->download()->signal_download_done(sigc::bind(sigc::mem_fun(*this, &DownloadList::received_finished), download));
    std::for_each(m_slotMapInsert.begin(), m_slotMapInsert.end(), download_list_call(*itr));

  } catch (torrent::local_error& e) {
    // Should perhaps relax this, just print an error and remove the
    // downloads?
    throw torrent::internal_error("Caught during DownloadList::insert(...): " + std::string(e.what()));
  }

  return itr;
}

void
DownloadList::erase(Download* download) {
  check_contains(download);

  erase(std::find(begin(), end(), download));
}

DownloadList::iterator
DownloadList::erase(iterator itr) {
  if (itr == end())
    throw torrent::internal_error("DownloadList::erase(...) could not find download.");

  close(*itr);

  control->core()->download_store()->remove(*itr);

  std::for_each(m_slotMapErase.begin(), m_slotMapErase.end(), download_list_call(*itr));

  torrent::download_remove(*(*itr)->download());
  delete *itr;

  return base_type::erase(itr);
}

// void
// DownloadList::save(Download* d) {
  
// }

void
DownloadList::open(Download* download) {
  try {

    open_throw(download);

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::open_throw(Download* download) {
  check_contains(download);

  if (download->download()->is_open())
    return;
  
  download->download()->open();

  std::for_each(m_slotMapOpen.begin(), m_slotMapOpen.end(), download_list_call(download));
}

void
DownloadList::close(Download* download) {
  try {

    close_throw(download);

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::close_throw(Download* download) {
  check_contains(download);

  if (!download->download()->is_open())
    return;

  if (download->download()->is_active())
    pause(download);
  
  // Save the torrent on close, this covers shutdown and if a torrent
  // is manually closed which would clear the progress data. For
  // better crash protection, save regulary in addition to this.
  //
  // Used to be in pause, but this was wrong for rehashing etc.
  //
  // Reconsider this save. Should be done explicitly when shutting down.
  //control->core()->download_store()->save(download);
  control->core()->hash_queue()->remove(download);

  download->download()->close();

  std::for_each(m_slotMapClose.begin(), m_slotMapClose.end(), download_list_call(download));
}

void
DownloadList::start(Download* download) {
  check_contains(download);

  download->variable()->set("state", (int64_t)1);

  resume(download);
}

void
DownloadList::stop(Download* download) {
  check_contains(download);

  download->variable()->set("state", (int64_t)0);

  pause(download);
}

void
DownloadList::resume(Download* download) {
  check_contains(download);

  try {

    if (download->download()->is_active())
      return;

    // Properly escape when resume get's called during hashing. The
    // 'state' is changed by the call to DownloadList::start so it
    // will automagically start afterwards.
    if (control->core()->hash_queue()->find(download) != control->core()->hash_queue()->end())
      return;

    download->variable()->set("state_changed", cachedTime.seconds());

    open_throw(download);

    // Manual or end-of-download rehashing clears the resume data so
    // we can just start the hashing again without clearing it again.
    //
    // It is also assumed the is_hash_checked flag gets cleared when
    // 'hashing' was set.
    if (!download->download()->is_hash_checked()) {

      // Set 'hashing' to started if hashing wasn't started, else keep
      // the old value.
      if (download->variable()->get_value("hashing") == Download::variable_hashing_stopped)
	download->variable()->set("hashing", Download::variable_hashing_started);

      control->core()->hash_queue()->insert(download);
      return;
    }

    if (download->is_done()) {
      download->set_connection_type(download->variable()->get_string("connection_seed"));
    } else {
      download->set_connection_type(download->variable()->get_string("connection_leech"));

      // For the moment, clear the resume data so we force hash-check
      // on non-complete downloads after a crash. This shouldn't be
      // needed, but for some reason linux 2.6 is very lazy about
      // updating mtime.
      download->download()->hash_resume_clear();
    }

    // Update the priority to ensure it has the correct
    // seeding/unfinished modifiers.
    download->set_priority(download->priority());
    download->download()->start();

    std::for_each(m_slotMapStart.begin(), m_slotMapStart.end(), download_list_call(download));

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::pause(Download* download) {
  check_contains(download);

  try {

    // Make sure we don't start hash checking a download that we won't
    // start.
    control->core()->hash_queue()->remove(download);

    if (!download->download()->is_active())
      return;

    download->download()->stop();
    download->download()->hash_resume_save();
    
    std::for_each(m_slotMapStop.begin(), m_slotMapStop.end(), download_list_call(download));

    download->variable()->set("state_changed", cachedTime.seconds());

    // Save the state after all the slots, etc have been called so we
    // include the modifications they may make.
    //control->core()->download_store()->save(download);

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::check_hash(Download* download) {
  check_contains(download);

  try {

    download->variable()->set("hashing", Download::variable_hashing_started);
    check_hash_throw(download);

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

// Throw in addition to not setting 'hashing'.
void
DownloadList::check_hash_throw(Download* download) {
  check_contains(download);

  close_throw(download);
  download->download()->hash_resume_clear();
  open_throw(download);

  // If any more stuff is added here, make sure resume etc are still
  // correct.
  control->core()->hash_queue()->insert(download);
}

void
DownloadList::hash_done(Download* download) {
  check_contains(download);

  if (!download->download()->is_hash_checked() ||
      download->download()->is_hash_checking() ||
      download->download()->is_active())
    throw torrent::internal_error("DownloadList::hash_done(...) download in invalid state.");

  // Need to find some sane conditional here. Can we check the total
  // downloaded to ensure something was transferred, thus we didn't
  // just hash an already completed torrent with lacking session data?
  //
  // Perhaps we should use a seperate variable or state, and check
  // that. Thus we can bork the download if the hash check doesn't
  // confirm all the data, avoiding large BW usage on f.ex. the
  // ReiserFS bug with >4GB files.

  int64_t hashing = download->variable()->get_value("hashing");
  download->variable()->set("hashing", Download::variable_hashing_stopped);

  switch (hashing) {
  case Download::variable_hashing_started:
    // Normal re/hashing.

    if (download->is_done())
      download->variable()->set("complete", (int64_t)1);
    
    // Save resume data so we update time-stamps and priorities if
    // they were invalid/changed when loading.
    download->download()->hash_resume_save();

    if (download->variable()->get_value("state") == 1)
      resume(download);

    return;

  case Download::variable_hashing_last:

    if (download->is_done()) {

      confirm_finished(download);

      if (download->variable()->get_value("state") == 1)
	resume(download);

    } else {
      download->set_message("Hash check on download completion found bad chunks.");
    }
    
    return;

  case Download::variable_hashing_stopped:
  default:
    // Either an error or someone wrote to the hashing variable...
    download->set_message("Hash check completed but the \"hashing\" variable is in an invalid state.");
    return;
  }
}

void
DownloadList::received_finished(Download* download) {
  check_contains(download);

  if (control->variable()->get_value("check_hash")) {
    // Set some 'checking_finished_thingie' variable to make hash_done
    // trigger correctly, also so it can bork on missing data.

    download->variable()->set("hashing", Download::variable_hashing_last);
    check_hash_throw(download);

  } else {
    confirm_finished(download);
  }
}

// The download must be open when we call this function.
void
DownloadList::confirm_finished(Download* download) {
  check_contains(download);

  // FIXME
  //torrent::download_set_priority(m_download, 2);

  download->variable()->set("complete", (int64_t)1);
  download->set_connection_type(download->variable()->get_string("connection_seed"));

  download->download()->tracker_list().send_completed();

  // Do this before the slots are called in case one of them closes
  // the download.
  if (!download->is_active() && control->variable()->get_value("session_on_completion") == 1) {
    download->download()->hash_resume_save();
    control->core()->download_store()->save(download);
  }

  std::for_each(m_slotMapFinished.begin(), m_slotMapFinished.end(), download_list_call(download));
}

}
