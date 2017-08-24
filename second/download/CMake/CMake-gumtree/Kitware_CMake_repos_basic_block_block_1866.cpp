{
#if defined(_WIN32) && defined(KWSYS_SYS_HAS_PSAPI)
  long pid = GetCurrentProcessId();
  HANDLE hProc;
  hProc = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, pid);
  if (hProc == 0) {
    return -1;
  }
  PROCESS_MEMORY_COUNTERS pmc;
  int ok = GetProcessMemoryInfo(hProc, &pmc, sizeof(pmc));
  CloseHandle(hProc);
  if (!ok) {
    return -2;
  }
  return pmc.WorkingSetSize / 1024;
#elif defined(__linux)
  SystemInformation::LongLong memUsed = 0;
  int ierr = GetFieldFromFile("/proc/self/status", "VmRSS:", memUsed);
  if (ierr) {
    return -1;
  }
  return memUsed;
#elif defined(__APPLE__)
  SystemInformation::LongLong memUsed = 0;
  pid_t pid = getpid();
  std::ostringstream oss;
  oss << "ps -o rss= -p " << pid;
  FILE* file = popen(oss.str().c_str(), "r");
  if (file == 0) {
    return -1;
  }
  oss.str("");
  while (!feof(file) && !ferror(file)) {
    char buf[256] = { '\0' };
    errno = 0;
    size_t nRead = fread(buf, 1, 256, file);
    if (ferror(file) && (errno == EINTR)) {
      clearerr(file);
    }
    if (nRead)
      oss << buf;
  }
  int ierr = ferror(file);
  pclose(file);
  if (ierr) {
    return -2;
  }
  std::istringstream iss(oss.str());
  iss >> memUsed;
  return memUsed;
#else
  return 0;
#endif
}