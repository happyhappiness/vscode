      includes.push_back(inc);
    } else {
      if (!isFirstLine || !startsWith(line, srcfilename)) {
        if (!quiet) {
          fprintf(stdout, "%s\n", line.c_str());
        }
      } else {
