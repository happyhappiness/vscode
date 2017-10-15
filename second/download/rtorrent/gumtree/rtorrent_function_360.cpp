void
receive_tracker_dump(const std::string& url, const char* data, size_t size) {
  const std::string& filename = rpc::call_command_string("log.tracker");

  if (filename.empty())
    return;

  std::fstream fstr(filename.c_str(), std::ios::out | std::ios::app);

  if (!fstr.is_open())
    return;

  fstr << "url: " << url << std::endl << "---" << std::endl;
  fstr.write(data, size);
  fstr << std::endl <<"---" << std::endl;
}