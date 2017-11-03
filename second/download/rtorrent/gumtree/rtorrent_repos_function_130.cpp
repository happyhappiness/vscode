torrent::Object
apply_execute_log(const torrent::Object& rawArgs) {
  if (rpc::execFile.log_fd() != -1) {
    ::close(rpc::execFile.log_fd());
    rpc::execFile.set_log_fd(-1);
  }

  if (rawArgs.is_string() && !rawArgs.as_string().empty()) {
    int logFd = open(rak::path_expand(rawArgs.as_string()).c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644);

    if (logFd < 0)
      throw torrent::input_error("Could not open execute log file.");

    rpc::execFile.set_log_fd(logFd);
    control->core()->push_log("Opened execute log file.");

  } else {
    control->core()->push_log("Closed execute log file.");
  }

  return torrent::Object();
}