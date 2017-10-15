    // they were invalid/changed while loading/hashing.
    rpc::call_command("d.complete.set", (int64_t)download->is_done(), rpc::make_target(download));
    torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));

    if (rpc::call_command_value("d.state", rpc::make_target(download)) == 1)
      resume(download, download->resume_flags());
    //rpc::commands.call_catch("scheduler.simple.resume", rpc::make_target(download), torrent::Object(), "Download event action failed: ");

    break;

  case Download::variable_hashing_last:

    if (download->is_done()) {
      confirm_finished(download);
    } else {
      download->set_message("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
      control->core()->push_log("Hash check on download completion found bad chunks, consider using \"safe_sync\".");
      rpc::commands.call_catch("event.download.hash_final_failed", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
    }

    // TODO: Should we skip the 'hash_done' event here?
    return;

  case Download::variable_hashing_stopped:
  default:
    // Either an error or someone wrote to the hashing variable...
    download->set_message("Hash check completed but the \"hashing\" variable is in an invalid state.");
    return;
  }

  rpc::commands.call_catch("event.download.hash_done", rpc::make_target(download), torrent::Object(), "Download event action failed: ");
}

void
DownloadList::hash_queue(Download* download, int type) {
  check_contains(download);

