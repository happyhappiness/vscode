bool
manager_equal_tied(const std::string& path, Download* download) {
  return path == rpc::call_command_d_string("d.get_tied_to_file", download);
}