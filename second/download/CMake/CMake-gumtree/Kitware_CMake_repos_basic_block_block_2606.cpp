(nextarg) {
          if (i == argc - 1) {
            return 1; // invalid command line
          }
          logfile = argv[i + 1];
        } else {
          logfile = arg.substr(logarg.length());
        }