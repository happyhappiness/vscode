//
//           Skomakerveien 33
//           3185 Skoppum, NORWAY

#include "config.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "exec_file.h"

namespace rpc {

int
ExecFile::execute(const char* file, char* const* argv) {
  pid_t childPid = fork();

  if (childPid == -1)
    throw torrent::input_error("ExecFile::execute(...) Fork failed.");

  if (childPid == 0) {
    // Close all fd's.
    for (int i = 0, last = sysconf(_SC_OPEN_MAX); i != last; i++)
      ::close(i);

    int result = execvp(file, argv);

    _exit(result);

