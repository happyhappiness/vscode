
  return torrent::Object();
}

void
apply_d_delete_tied(core::Download* download) {
  const std::string& tie = rpc::call_command_d_string("d.get_tied_to_file", download);

  if (tie.empty())
    return;

  if (::unlink(rak::path_expand(tie).c_str()) == -1)
    control->core()->push_log_std("Could not unlink tied file: " + std::string(rak::error_number::current().c_str()));

  rpc::call_command_d("d.set_tied_to_file", download, std::string());
}

void
apply_d_connection_type(core::Download* download, const std::string& name) {
  torrent::Download::ConnectionType connType;

