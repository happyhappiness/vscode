    // Command to report progress for a build

    else if (args[1] == "cmake_progress_report" && args.size() >= 3)

      {

      // This has been superseded by cmake_echo_color --progress-*

      // options.  We leave it here to avoid errors if somehow this

      // is invoked by an existing makefile without regenerating.

      return 0;

      }



