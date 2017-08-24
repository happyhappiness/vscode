        fprintf(progFile,"%i\n",count);
        fclose(progFile);
        }
      return 0;
      }

    // Command to report progress for a build
    else if (args[1] == "cmake_progress_report" && args.size() >= 4)
      {
      std::string dirName = args[2];
      dirName += "/Progress";
      std::string fName;
