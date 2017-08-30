           target.GetPostBuildCommands().begin(); 
         cr != target.GetPostBuildCommands().end(); ++cr)
      {
      cmCustomCommand cc(*cr);
      cc.ExpandVariables(*m_Makefile);
      char *output = new char [
        strlen(m_Makefile->GetStartOutputDirectory()) + 
        strlen(libName) + 30];
      sprintf(output,"%s/%s_force_%i",
              m_Makefile->GetStartOutputDirectory(),
              libName, count);
      std::vector<std::string> args;
      // This is a hack to fix a problem with cmCustomCommand
      // The cmCustomCommand should store the arguments as a vector
      // and not a string, and the cmAddCustomTargetCommand should
      // not EscapeSpaces.
      args.push_back("This is really a single argument do not escape spaces");
      args.push_back(cc.GetArguments());
      m_Makefile->AddCustomCommandToOutput(output, 
                                           cc.GetCommand().c_str(), 
                                           args, 
                                           0, 
                                           cc.GetDepends());
      cmSourceFile* outsf = 
        m_Makefile->GetSourceFileWithOutput(output);
      target.GetSourceFiles().push_back(outsf);
