       }

    } else {

      if (!isFirstLine || !startsWith(line, srcfile)) {

        if (!ignoreErrors) {

          // suppress errors when cl is fed with a rc file

          fprintf(stdout, "%s\n", line.c_str());

        }

      } else {

