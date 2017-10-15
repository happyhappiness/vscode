void
apply_d_delete_tied(core::Download* download) {
  const std::string& tie = rpc::call_command_d_string("get_d_tied_to_file", download);

  if (tie.empty())
    return;

  if (::unlink(rak::path_expand(tie).c_str()) == -1)
    control->core()->push_log_std("Could not unlink tied file: " + std::string(rak::error_number::current().c_str()));

  rpc::call_command_d("set_d_tied_to_file", download, std::string());
}