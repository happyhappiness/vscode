void
Control::set_working_directory(const std::string& dir) {
  if (::chdir(dir.c_str()) != 0)
    throw torrent::input_error("Could not change working directory.");
}