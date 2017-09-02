void ctest::ProcessDirectory(int &passed, int &failed)
{
  // does the DartTestfile.txt exist ?
  if(!cmSystemTools::FileExists("DartTestfile.txt"))
    {
    return;
    }
  
  // parse the file
  std::ifstream fin("DartTestfile.txt");
  if(!fin)
    {
    return;
    }

  std::string name;
  std::vector<std::string> args;
  cmRegularExpression var(this->m_RegExp.c_str());

  while ( fin )
    {
    if(cmSystemTools::ParseFunction(fin, name, args))
      {
      if (name == "SUBDIRS")
        {
        std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
        for(std::vector<std::string>::iterator j = args.begin();
            j != args.end(); ++j)
          {   
          std::string nwd = cwd + "/";
          nwd += *j;
          if (cmSystemTools::FileIsDirectory(nwd.c_str()))
            {
            std::cerr << "Changing directory into " << nwd.c_str() << "\n";
            cmSystemTools::ChangeDirectory(nwd.c_str());
            this->ProcessDirectory(passed,failed);
            }
          }
        // return to the original directory
        cmSystemTools::ChangeDirectory(cwd.c_str());
        }
      
      if (name == "ADD_TEST")
        {
        if (this->m_UseRegExp && !var.find(args[0].c_str()))
          {
          continue;
          }
        fprintf(stderr,"Testing %-30s ",args[0].c_str());
        //std::cerr << "Testing " << args[0] << " ... ";
        // find the test executable
        std::string testCommand = this->FindExecutable(args[1].c_str());
        // add the arguments
        std::vector<std::string>::iterator j = args.begin();
        ++j;
        ++j;
        for(;j != args.end(); ++j)
          {   
          testCommand += " ";
          testCommand += *j;
          }
        /**
         * Run an executable command and put the stdout in output.
         */
        std::string output;
        int retVal;
        
        if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                       retVal, false) || retVal != 0)
          {
          fprintf(stderr,"***Failed\n");
          if (output != "")
            {
            std::cerr << output.c_str() << "\n";
            }
          failed++;
          }
        else
          {
          fprintf(stderr,"   Passed\n");
          if (output != "")
            {
            std::cerr << output.c_str() << "\n";
            }
          passed++;
          }
        }
      }
    }
  
}