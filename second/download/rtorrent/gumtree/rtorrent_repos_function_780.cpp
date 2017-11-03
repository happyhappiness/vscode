Lockfile::process_type
Lockfile::locked_by() const {
  int fd = ::open(m_path.c_str(), O_RDONLY);
  
  if (fd < 0)
    return process_type(std::string(), 0);

  char first[256];
  char* last = first + std::max<ssize_t>(read(fd, first, 255), 0);

  *last = '\0';
  ::close(fd);

  char* endHostname = std::find_if(first, last, lockfile_valid_hostname());
  char* beginPid = endHostname;
  char* endPid;

  long long int pid;

  if (beginPid + 2 >= last ||
      *(beginPid++) != ':' ||
      *(beginPid++) != '+' ||
      (pid = strtoll(beginPid, &endPid, 10)) == 0 ||
      endPid == NULL)
    return process_type(std::string(), 0);
    
  return process_type(std::string(first, endHostname), pid);
}