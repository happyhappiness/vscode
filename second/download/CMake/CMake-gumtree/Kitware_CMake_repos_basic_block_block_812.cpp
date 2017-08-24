(pipe == cmsysProcess_Pipe_STDERR) {
        std::cerr << line << "\n";
      } else if (pipe == cmsysProcess_Pipe_STDOUT) {
        std::cout << line << "\n";
      }