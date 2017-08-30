        fprintf(progFile,"%i\n",count);

        fclose(progFile);

        }

#endif

      return 0;

      }



    // Command to report progress for a build

    else if (args[1] == "cmake_progress_report" && args.size() >= 4)

      {

#if defined(CMAKE_BUILD_WITH_CMAKE)

      std::string dirName = args[2];

      dirName += "/Progress";

      std::string fName;

