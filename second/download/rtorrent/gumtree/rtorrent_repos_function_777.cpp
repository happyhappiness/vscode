bool
Lockfile::is_stale() {
  process_type process = locked_by();

  char buf[256];
  
  if (process.second <= 0 ||
      ::gethostname(buf, 255) != 0 || buf != process.first)
    return false;
      
  return ::kill(process.second, 0) != 0 && errno != EPERM;
}