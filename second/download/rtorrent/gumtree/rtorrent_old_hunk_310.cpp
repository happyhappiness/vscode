#include <rak/path.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "exec_file.h"
#include "parse.h"

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
        write(m_logFd, " ", 1);

      write(m_logFd, *itr, std::strlen(*itr));
    }

    write(m_logFd, "\n---\n", sizeof("\n---\n"));
  }

  int pipeFd[2];

  if ((flags & flag_capture) && pipe(pipeFd))
    throw torrent::input_error("ExecFile::execute(...) Pipe creation failed.");
