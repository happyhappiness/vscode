    delete download;

    m_slotFinished();
    return;
  }

  // When a download scheduler is implemented, this is handled by the
  // above insertion into download list.
  if (m_session) {
    // This torrent was queued for hashing or hashing when the session
    // file was saved. Or it was in a started state.
    if (rpc::call_command_d_value("get_d_hashing", download) != Download::variable_hashing_stopped ||
