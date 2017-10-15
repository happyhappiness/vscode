
namespace rpc {

// Close m_logFd.

int
ExecFile::execute(const char* file, char* const* argv, int flags) {
  // Write the execued command and its parameters to the log fd.
  if (m_logFd != -1) {
    for (char* const* itr = argv; *itr != NULL; itr++) {
      if (itr == argv)
        write(m_logFd, "\n---\n", sizeof("\n---\n"));
      else
