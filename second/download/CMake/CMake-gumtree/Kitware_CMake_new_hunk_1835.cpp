  return cmSystemTools::RunCommand(command, output, foo, dir, verbose);

}



#if defined(WIN32) && !defined(__CYGWIN__)

// use this for shell commands like echo and dir

bool RunCommandViaSystem(const char* command,

                         const char* dir,

