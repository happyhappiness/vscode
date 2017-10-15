    *str >> *object;
    
    // Catch, delete.
    if (str->fail())
      throw torrent::input_error("Could not create download, the input is not a valid torrent.");

    torrent::Download d = torrent::download_add(object);

    iterator itr = Base::insert(end(), new Download(d));

    (*itr)->download()->signal_download_done(sigc::bind(sigc::mem_fun(*this, &DownloadList::finished), *itr));
    std::for_each(m_slotMapInsert.begin(), m_slotMapInsert.end(), download_list_call(*itr));

    return itr;

  } catch (torrent::local_error& e) {
    delete object;

    if (printLog)
      control->core()->push_log(e.what());

    return end();
  }
}

DownloadList::iterator
DownloadList::erase(iterator itr) {
  // Make safe to erase active downloads.

  if ((*itr)->download()->is_active())
    throw std::logic_error("DownloadList::erase(...) called on an active download.");

  std::for_each(m_slotMapErase.begin(), m_slotMapErase.end(), download_list_call(*itr));

  torrent::download_remove(*(*itr)->download());
  delete *itr;

  return Base::erase(itr);
}

void
DownloadList::open(Download* d) {
  try {

    if (!d->download()->is_open())
      std::for_each(m_slotMapOpen.begin(), m_slotMapOpen.end(), download_list_call(d));

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::close(Download* d) {
  try {

    if (d->download()->is_active())
      std::for_each(m_slotMapStop.begin(), m_slotMapStop.end(), download_list_call(d));

    if (d->download()->is_open())
      std::for_each(m_slotMapClose.begin(), m_slotMapClose.end(), download_list_call(d));

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::start(Download* d) {
  d->variable()->set("state", "started");

  resume(d);
}

void
DownloadList::stop(Download* d) {
  d->variable()->set("state", "stopped");

  pause(d);
}

void
DownloadList::resume(Download* d) {
  try {
    if (!d->download()->is_open())
      std::for_each(m_slotMapOpen.begin(), m_slotMapOpen.end(), download_list_call(d));
      
    if (d->download()->is_hash_checked())
      std::for_each(m_slotMapStart.begin(), m_slotMapStart.end(), download_list_call(d));
    else
      // TODO: This can cause infinit looping?
      control->core()->hash_queue().insert(d, sigc::bind(sigc::mem_fun(*this, &DownloadList::resume), d));

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::pause(Download* d) {
  try {

    if (d->download()->is_active())
      std::for_each(m_slotMapStop.begin(), m_slotMapStop.end(), download_list_call(d));

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}

void
DownloadList::clear() {
  std::for_each(begin(), end(), rak::call_delete<Download>());

  Base::clear();
}

void
DownloadList::finished(Download* d) {
  std::for_each(m_slotMapFinished.begin(), m_slotMapFinished.end(), download_list_call(d));
}

}
