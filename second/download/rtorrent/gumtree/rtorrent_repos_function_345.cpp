void
DownloadList::activate(display::Frame* frame, bool focus) {
  if (is_active())
    throw torrent::internal_error("ui::DownloadList::activate() called on an already activated object");

  m_frame = frame;

  control->input()->push_back(&m_bindings);
  control->core()->download_list()->slot_map_erase()["0_download_list"] = sigc::mem_fun(this, &DownloadList::receive_download_erased);

  activate_display(DISPLAY_DOWNLOAD_LIST);
}