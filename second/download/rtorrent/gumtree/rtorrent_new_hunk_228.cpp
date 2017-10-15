//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#include "config.h"

#include <string>
#include <unistd.h>
#include <rak/path.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "exec_file.h"
#include "parse.h"

namespace rpc {

// Close m_logFd.

int
ExecFile::execute(const char* file, char* const* argv) {
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

  pid_t childPid = fork();

  if (childPid == -1)
    throw torrent::input_error("ExecFile::execute(...) Fork failed.");

  if (childPid == 0) {
    ::close(0);
    ::close(1);
    ::close(2);

    if (m_logFd != -1) {
      dup2(m_logFd, 1);
      dup2(m_logFd, 2);
    }

    // Close all fd's.
    for (int i = 3, last = sysconf(_SC_OPEN_MAX); i != last; i++)
      ::close(i);

    int result = execvp(file, argv);

    _exit(result);

