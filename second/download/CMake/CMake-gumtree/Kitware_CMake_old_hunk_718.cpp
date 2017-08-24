#ifdef _WIN32
  std::string comspec = "cmw9xcom.exe";
  cmSystemTools::SetWindows9xComspecSubstitute(comspec.c_str());
#endif
  return 1;
}



void CMakeCommandUsage(const char* program)
{
  cmOStringStream errorStream;

#ifdef CMAKE_BUILD_WITH_CMAKE
  errorStream
    << "cmake version " << cmVersion::GetCMakeVersion() << "\n";
#else
  errorStream
    << "cmake bootstrap\n";
#endif
  // If you add new commands, change here,
  // and in cmakemain.cxx in the options table
  errorStream
    << "Usage: " << program << " -E [command] [arguments ...]\n"
    << "Available commands: \n"
    << "  chdir dir cmd [args]...   - run command in a given directory\n"
    << "  compare_files file1 file2 - check if file1 is same as file2\n"
    << "  copy file destination     - copy file to destination (either file "
       "or directory)\n"
    << "  copy_directory source destination   - copy directory 'source' "
       "content to directory 'destination'\n"
    << "  copy_if_different in-file out-file  - copy file if input has "
       "changed\n"
    << "  echo [string]...          - displays arguments as text\n"
    << "  echo_append [string]...   - displays arguments as text but no new "
       "line\n"
    << "  environment               - display the current environment\n"
    << "  make_directory dir        - create a directory\n"
    << "  md5sum file1 [...]        - compute md5sum of files\n"
    << "  remove [-f] file1 file2 ... - remove the file(s), use -f to force "
       "it\n"
    << "  remove_directory dir      - remove a directory and its contents\n"
    << "  rename oldname newname    - rename a file or directory "
       "(on one volume)\n"
    << "  tar [cxt][vfz][cvfj] file.tar [file/dir1 file/dir2 ...]\n"
    << "                            - create or extract a tar or zip archive\n"
    << "  time command [args] ...   - run command and return elapsed time\n"
    << "  touch file                - touch a file.\n"
    << "  touch_nocreate file       - touch a file but do not create it.\n"
#if defined(_WIN32) && !defined(__CYGWIN__)
    << "Available on Windows only:\n"
    << "  comspec                   - on windows 9x use this for RunCommand\n"
    << "  delete_regv key           - delete registry value\n"
    << "  env_vs8_wince sdkname     - displays a batch file which sets the "
       "environment for the provided Windows CE SDK installed in VS2005\n"
    << "  env_vs9_wince sdkname     - displays a batch file which sets the "
       "environment for the provided Windows CE SDK installed in VS2008\n"
    << "  write_regv key value      - write registry value\n"
#else
    << "Available on UNIX only:\n"
    << "  create_symlink old new    - create a symbolic link new -> old\n"
#endif
    ;

  cmSystemTools::Error(errorStream.str().c_str());
}

int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
{
  // IF YOU ADD A NEW COMMAND, DOCUMENT IT ABOVE and in cmakemain.cxx
  if (args.size() > 1)
    {
    // Copy file
    if (args[1] == "copy" && args.size() == 4)
      {
      if(!cmSystemTools::cmCopyFile(args[2].c_str(), args[3].c_str()))
        {
        std::cerr << "Error copying file \"" << args[2].c_str()
                  << "\" to \"" << args[3].c_str() << "\".\n";
        return 1;
        }
      return 0;
      }

    // Copy file if different.
    if (args[1] == "copy_if_different" && args.size() == 4)
      {
      if(!cmSystemTools::CopyFileIfDifferent(args[2].c_str(),
          args[3].c_str()))
        {
        std::cerr << "Error copying file (if different) from \""
                  << args[2].c_str() << "\" to \"" << args[3].c_str()
                  << "\".\n";
        return 1;
        }
      return 0;
      }

    // Copy directory content
    if (args[1] == "copy_directory" && args.size() == 4)
      {
      if(!cmSystemTools::CopyADirectory(args[2].c_str(), args[3].c_str()))
        {
        std::cerr << "Error copying directory from \""
                  << args[2].c_str() << "\" to \"" << args[3].c_str()
                  << "\".\n";
        return 1;
        }
      return 0;
      }

    // Rename a file or directory
    if (args[1] == "rename" && args.size() == 4)
      {
      if(!cmSystemTools::RenameFile(args[2].c_str(), args[3].c_str()))
        {
        std::string e = cmSystemTools::GetLastSystemError();
        std::cerr << "Error renaming from \""
                  << args[2].c_str() << "\" to \"" << args[3].c_str()
                  << "\": " << e << "\n";
        return 1;
        }
      return 0;
      }

    // Compare files
    if (args[1] == "compare_files" && args.size() == 4)
      {
      if(cmSystemTools::FilesDiffer(args[2].c_str(), args[3].c_str()))
        {
        std::cerr << "Files \""
                  << args[2].c_str() << "\" to \"" << args[3].c_str()
                  << "\" are different.\n";
        return 1;
        }
      return 0;
      }

    // Echo string
    else if (args[1] == "echo" )
      {
      unsigned int cc;
      const char* space = "";
      for ( cc = 2; cc < args.size(); cc ++ )
        {
        std::cout << space << args[cc];
        space = " ";
        }
      std::cout << std::endl;
      return 0;
      }

    // Echo string no new line
    else if (args[1] == "echo_append" )
      {
      unsigned int cc;
      const char* space = "";
      for ( cc = 2; cc < args.size(); cc ++ )
        {
        std::cout << space << args[cc];
        space = " ";
        }
      return 0;
      }

#if defined(CMAKE_BUILD_WITH_CMAKE)
    // Command to create a symbolic link.  Fails on platforms not
    // supporting them.
    else if (args[1] == "environment" )
      {
      std::vector<std::string> env = cmSystemTools::GetEnvironmentVariables();
      std::vector<std::string>::iterator it;
      for ( it = env.begin(); it != env.end(); ++ it )
        {
        std::cout << it->c_str() << std::endl;
        }
      return 0;
      }
#endif

    else if (args[1] == "make_directory" && args.size() == 3)
      {
      if(!cmSystemTools::MakeDirectory(args[2].c_str()))
        {
        std::cerr << "Error making directory \"" << args[2].c_str()
                  << "\".\n";
        return 1;
        }
      return 0;
      }

    else if (args[1] == "remove_directory" && args.size() == 3)
      {
      if(cmSystemTools::FileIsDirectory(args[2].c_str()) &&
         !cmSystemTools::RemoveADirectory(args[2].c_str()))
        {
        std::cerr << "Error removing directory \"" << args[2].c_str()
                  << "\".\n";
        return 1;
        }
      return 0;
      }

    // Remove file
    else if (args[1] == "remove" && args.size() > 2)
      {
      bool force = false;
      for (std::string::size_type cc = 2; cc < args.size(); cc ++)
        {
        if(args[cc] == "\\-f" || args[cc] == "-f")
          {
          force = true;
          }
        else
          {
          // Complain if the file could not be removed, still exists,
          // and the -f option was not given.
          if(!cmSystemTools::RemoveFile(args[cc].c_str()) && !force &&
             cmSystemTools::FileExists(args[cc].c_str()))
            {
            return 1;
            }
          }
        }
      return 0;
      }
    // Touch file
    else if (args[1] == "touch" && args.size() > 2)
      {
      for (std::string::size_type cc = 2; cc < args.size(); cc ++)
        {
        // Complain if the file could not be removed, still exists,
        // and the -f option was not given.
        if(!cmSystemTools::Touch(args[cc].c_str(), true))
          {
          return 1;
          }
        }
      return 0;
      }
    // Touch file
    else if (args[1] == "touch_nocreate" && args.size() > 2)
      {
      for (std::string::size_type cc = 2; cc < args.size(); cc ++)
        {
        // Complain if the file could not be removed, still exists,
        // and the -f option was not given.
        if(!cmSystemTools::Touch(args[cc].c_str(), false))
          {
          return 1;
          }
        }
      return 0;
      }

    // Clock command
    else if (args[1] == "time" && args.size() > 2)
      {
      std::string command = args[2];
      for (std::string::size_type cc = 3; cc < args.size(); cc ++)
        {
        command += " ";
        command += args[cc];
        }

      clock_t clock_start, clock_finish;
      time_t time_start, time_finish;

      time(&time_start);
      clock_start = clock();
      int ret =0;
      cmSystemTools::RunSingleCommand(command.c_str(), 0, &ret);

      clock_finish = clock();
      time(&time_finish);

      double clocks_per_sec = static_cast<double>(CLOCKS_PER_SEC);
      std::cout << "Elapsed time: "
        << static_cast<long>(time_finish - time_start) << " s. (time)"
        << ", "
        << static_cast<double>(clock_finish - clock_start) / clocks_per_sec
        << " s. (clock)"
        << "\n";
      return ret;
      }
    // Command to calculate the md5sum of a file
    else if (args[1] == "md5sum" && args.size() >= 3)
      {
      char md5out[32];
      int retval = 0;
      for (std::string::size_type cc = 2; cc < args.size(); cc ++)
        {
        const char *filename = args[cc].c_str();
        // Cannot compute md5sum of a directory
        if(cmSystemTools::FileIsDirectory(filename))
          {
          std::cerr << "Error: " << filename << " is a directory" << std::endl;
          retval++;
          }
        else if(!cmSystemTools::ComputeFileMD5(filename, md5out))
          {
          // To mimic md5sum behavior in a shell:
          std::cerr << filename << ": No such file or directory" << std::endl;
          retval++;
          }
        else
          {
          std::cout << std::string(md5out,32) << "  " << filename << std::endl;
          }
        }
      return retval;
      }

    // Command to change directory and run a program.
    else if (args[1] == "chdir" && args.size() >= 4)
      {
      std::string directory = args[2];
      if(!cmSystemTools::FileExists(directory.c_str()))
        {
        cmSystemTools::Error("Directory does not exist for chdir command: ",
                             args[2].c_str());
        return 1;
        }

      std::string command = "\"";
      command += args[3];
      command += "\"";
      for (std::string::size_type cc = 4; cc < args.size(); cc ++)
        {
        command += " \"";
        command += args[cc];
        command += "\"";
        }
      int retval = 0;
      int timeout = 0;
      if ( cmSystemTools::RunSingleCommand(command.c_str(), 0, &retval,
             directory.c_str(), cmSystemTools::OUTPUT_NORMAL, timeout) )
        {
        return retval;
        }

      return 1;
      }

    // Command to start progress for a build
    else if (args[1] == "cmake_progress_start" && args.size() == 4)
      {
      // basically remove the directory
      std::string dirName = args[2];
      dirName += "/Progress";
      cmSystemTools::RemoveADirectory(dirName.c_str());

      // is the last argument a filename that exists?
      FILE *countFile = fopen(args[3].c_str(),"r");
      int count;
      if (countFile)
        {
        if (1!=fscanf(countFile,"%i",&count))
          {
          cmSystemTools::Message("Could not read from count file.");
          }
        fclose(countFile);
        }
      else
        {
        count = atoi(args[3].c_str());
        }
      if (count)
        {
        cmSystemTools::MakeDirectory(dirName.c_str());
        // write the count into the directory
        std::string fName = dirName;
        fName += "/count.txt";
        FILE *progFile = fopen(fName.c_str(),"w");
        if (progFile)
          {
          fprintf(progFile,"%i\n",count);
          fclose(progFile);
          }
        }
      return 0;
      }

    // Command to report progress for a build
    else if (args[1] == "cmake_progress_report" && args.size() >= 3)
      {
      std::string dirName = args[2];
      dirName += "/Progress";
      std::string fName;
      FILE *progFile;

      // read the count
      fName = dirName;
      fName += "/count.txt";
      progFile = fopen(fName.c_str(),"r");
      int count = 0;
      if (!progFile)
        {
        return 0;
        }
      else
        {
        if (1!=fscanf(progFile,"%i",&count))
          {
          cmSystemTools::Message("Could not read from progress file.");
          }
        fclose(progFile);
        }
      unsigned int i;
      for (i = 3; i < args.size(); ++i)
        {
        fName = dirName;
        fName += "/";
        fName += args[i];
        progFile = fopen(fName.c_str(),"w");
        if (progFile)
          {
          fprintf(progFile,"empty");
          fclose(progFile);
          }
        }
      int fileNum = static_cast<int>
        (cmsys::Directory::GetNumberOfFilesInDirectory(dirName.c_str()));
      if (count > 0)
        {
        // print the progress
        fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);
        }
      return 0;
      }

    // Command to create a symbolic link.  Fails on platforms not
    // supporting them.
    else if (args[1] == "create_symlink" && args.size() == 4)
      {
      const char* destinationFileName = args[3].c_str();
      if ( cmSystemTools::FileExists(destinationFileName) )
        {
        if ( cmSystemTools::FileIsSymlink(destinationFileName) )
          {
          if ( !cmSystemTools::RemoveFile(destinationFileName) ||
            cmSystemTools::FileExists(destinationFileName) )
            {
            return 0;
            }
          }
        else
          {
          return 0;
          }
        }
      return cmSystemTools::CreateSymlink(args[2].c_str(),
                                          args[3].c_str())? 0:1;
      }

    // Internal CMake shared library support.
    else if (args[1] == "cmake_symlink_library" && args.size() == 5)
      {
      return cmake::SymlinkLibrary(args);
      }
    // Internal CMake versioned executable support.
    else if (args[1] == "cmake_symlink_executable" && args.size() == 4)
      {
      return cmake::SymlinkExecutable(args);
      }

#if defined(CMAKE_HAVE_VS_GENERATORS)
    // Internal CMake support for calling Visual Studio macros.
    else if (args[1] == "cmake_call_visual_studio_macro" && args.size() >= 4)
      {
      // args[2] = full path to .sln file or "ALL"
      // args[3] = name of Visual Studio macro to call
      // args[4..args.size()-1] = [optional] args for Visual Studio macro

      std::string macroArgs;

      if (args.size() > 4)
        {
        macroArgs = args[4];

        for (size_t i = 5; i < args.size(); ++i)
          {
          macroArgs += " ";
          macroArgs += args[i];
          }
        }

      return cmCallVisualStudioMacro::CallMacro(args[2], args[3],
        macroArgs, true);
      }
#endif

    // Internal CMake dependency scanning support.
    else if (args[1] == "cmake_depends" && args.size() >= 6)
      {
      // Use the make system's VERBOSE environment variable to enable
      // verbose output. This can be skipped by also setting CMAKE_NO_VERBOSE
      // (which is set by the Eclipse and KDevelop generators).
      bool verbose = ((cmSystemTools::GetEnv("VERBOSE") != 0)
                       && (cmSystemTools::GetEnv("CMAKE_NO_VERBOSE") == 0));

      // Create a cmake object instance to process dependencies.
      cmake cm;
      std::string gen;
      std::string homeDir;
      std::string startDir;
      std::string homeOutDir;
      std::string startOutDir;
      std::string depInfo;
      bool color = false;
      if(args.size() >= 8)
        {
        // Full signature:
        //
        //   -E cmake_depends <generator>
        //                    <home-src-dir> <start-src-dir>
        //                    <home-out-dir> <start-out-dir>
        //                    <dep-info> [--color=$(COLOR)]
        //
        // All paths are provided.
        gen = args[2];
        homeDir = args[3];
        startDir = args[4];
        homeOutDir = args[5];
        startOutDir = args[6];
        depInfo = args[7];
        if(args.size() >= 9 &&
           args[8].length() >= 8 &&
           args[8].substr(0, 8) == "--color=")
          {
          // Enable or disable color based on the switch value.
          color = (args[8].size() == 8 ||
                   cmSystemTools::IsOn(args[8].substr(8).c_str()));
          }
        }
      else
        {
        // Support older signature for existing makefiles:
        //
        //   -E cmake_depends <generator>
        //                    <home-out-dir> <start-out-dir>
        //                    <dep-info>
        //
        // Just pretend the source directories are the same as the
        // binary directories so at least scanning will work.
        gen = args[2];
        homeDir = args[3];
        startDir = args[4];
        homeOutDir = args[3];
        startOutDir = args[3];
        depInfo = args[5];
        }

      // Create a local generator configured for the directory in
      // which dependencies will be scanned.
      homeDir = cmSystemTools::CollapseFullPath(homeDir.c_str());
      startDir = cmSystemTools::CollapseFullPath(startDir.c_str());
      homeOutDir = cmSystemTools::CollapseFullPath(homeOutDir.c_str());
      startOutDir = cmSystemTools::CollapseFullPath(startOutDir.c_str());
      cm.SetHomeDirectory(homeDir.c_str());
      cm.SetStartDirectory(startDir.c_str());
      cm.SetHomeOutputDirectory(homeOutDir.c_str());
      cm.SetStartOutputDirectory(startOutDir.c_str());
      if(cmGlobalGenerator* ggd = cm.CreateGlobalGenerator(gen.c_str()))
        {
        cm.SetGlobalGenerator(ggd);
        cmsys::auto_ptr<cmLocalGenerator> lgd(ggd->CreateLocalGenerator());
        lgd->GetMakefile()->SetStartDirectory(startDir.c_str());
        lgd->GetMakefile()->SetStartOutputDirectory(startOutDir.c_str());
        lgd->GetMakefile()->MakeStartDirectoriesCurrent();

        // Actually scan dependencies.
        return lgd->UpdateDependencies(depInfo.c_str(),
                                       verbose, color)? 0 : 2;
        }
      return 1;
      }

    // Internal CMake link script support.
    else if (args[1] == "cmake_link_script" && args.size() >= 3)
      {
      return cmake::ExecuteLinkScript(args);
      }

    // Internal CMake unimplemented feature notification.
    else if (args[1] == "cmake_unimplemented_variable")
      {
      std::cerr << "Feature not implemented for this platform.";
      if(args.size() == 3)
        {
        std::cerr << "  Variable " << args[2] << " is not set.";
        }
      std::cerr << std::endl;
      return 1;
      }
    else if (args[1] == "vs_link_exe")
      {
      return cmake::VisualStudioLink(args, 1);
      }
    else if (args[1] == "vs_link_dll")
      {
      return cmake::VisualStudioLink(args, 2);
      }
#ifdef CMAKE_BUILD_WITH_CMAKE
    // Internal CMake color makefile support.
    else if (args[1] == "cmake_echo_color")
      {
      return cmake::ExecuteEchoColor(args);
      }
    else if (args[1] == "cmake_automoc")
      {
        cmQtAutomoc automoc;
        const char *config = args[3].empty() ? 0 : args[3].c_str();
        bool automocSuccess = automoc.Run(args[2].c_str(), config);
        return automocSuccess ? 0 : 1;
      }
#endif

    // Tar files
    else if (args[1] == "tar" && args.size() > 3)
      {
      std::string flags = args[2];
      std::string outFile = args[3];
      std::vector<cmStdString> files;
      for (std::string::size_type cc = 4; cc < args.size(); cc ++)
        {
        files.push_back(args[cc]);
        }
      bool gzip = false;
      bool bzip2 = false;
      bool verbose = false;
      if ( flags.find_first_of('j') != flags.npos )
        {
        bzip2 = true;
        }
      if ( flags.find_first_of('z') != flags.npos )
        {
        gzip = true;
        }
      if ( flags.find_first_of('v') != flags.npos )
        {
        verbose = true;
        }

      if ( flags.find_first_of('t') != flags.npos )
        {
        if ( !cmSystemTools::ListTar(outFile.c_str(), gzip, verbose) )
          {
          cmSystemTools::Error("Problem creating tar: ", outFile.c_str());
          return 1;
          }
        }
      else if ( flags.find_first_of('c') != flags.npos )
        {
        if ( !cmSystemTools::CreateTar(
               outFile.c_str(), files, gzip, bzip2, verbose) )
          {
          cmSystemTools::Error("Problem creating tar: ", outFile.c_str());
          return 1;
          }
        }
      else if ( flags.find_first_of('x') != flags.npos )
        {
        if ( !cmSystemTools::ExtractTar(
            outFile.c_str(), gzip, verbose) )
          {
          cmSystemTools::Error("Problem extracting tar: ", outFile.c_str());
          return 1;
          }
#ifdef WIN32
        // OK, on windows 7 after we untar some files,
        // sometimes we can not rename the directory after
        // the untar is done. This breaks the external project
        // untar and rename code.  So, by default we will wait
        // 1/10th of a second after the untar.  If CMAKE_UNTAR_DELAY
        // is set in the env, its value will be used instead of 100.
        int delay = 100;
        const char* delayVar = cmSystemTools::GetEnv("CMAKE_UNTAR_DELAY");
        if(delayVar)
          {
          delay = atoi(delayVar);
          }
        if(delay)
          {
          cmSystemTools::Delay(delay);
          }
#endif
        }
      return 0;
      }

#if defined(CMAKE_BUILD_WITH_CMAKE)
    // Internal CMake Fortran module support.
    else if (args[1] == "cmake_copy_f90_mod" && args.size() >= 4)
      {
      return cmDependsFortran::CopyModule(args)? 0 : 1;
      }
#endif

#if defined(_WIN32) && !defined(__CYGWIN__)
    // Write registry value
    else if (args[1] == "write_regv" && args.size() > 3)
      {
      return cmSystemTools::WriteRegistryValue(args[2].c_str(),
                                               args[3].c_str()) ? 0 : 1;
      }

    // Delete registry value
    else if (args[1] == "delete_regv" && args.size() > 2)
      {
      return cmSystemTools::DeleteRegistryValue(args[2].c_str()) ? 0 : 1;
      }
    // Remove file
    else if (args[1] == "comspec" && args.size() > 2)
      {
      unsigned int cc;
      std::string command = args[2];
      for ( cc = 3; cc < args.size(); cc ++ )
        {
        command += " " + args[cc];
        }
      return cmWin32ProcessExecution::Windows9xHack(command.c_str());
      }
    else if (args[1] == "env_vs8_wince" && args.size() == 3)
      {
      return cmake::WindowsCEEnvironment("8.0", args[2]);
      }
    else if (args[1] == "env_vs9_wince" && args.size() == 3)
      {
      return cmake::WindowsCEEnvironment("9.0", args[2]);
      }
#endif
    }

  ::CMakeCommandUsage(args[0].c_str());
  return 1;
}

