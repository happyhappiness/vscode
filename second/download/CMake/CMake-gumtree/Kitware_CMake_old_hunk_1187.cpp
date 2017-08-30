       }

    } else {

      if (!isFirstLine || !startsWith(line, srcfile)) {

        fprintf(stdout, "%s\n", line.c_str());

      } else {

        isFirstLine = false;

      }

    }

  }



  if (!success)

    return exit_code;



  // don't update .d until/unless we succeed compilation

  outputDepFile(dfile, objfile, includes);



  return 0;

}

