      includes.push_back(inc);

    } else {

      if (!isFirstLine || !startsWith(line, srcfilename)) {

        if (!quiet || exit_code != 0) {

          fprintf(stdout, "%s\n", line.c_str());

        }

      } else {

