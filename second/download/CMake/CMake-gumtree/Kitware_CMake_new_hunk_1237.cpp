           target.GetPostBuildCommands().begin(); 
         cr != target.GetPostBuildCommands().end(); ++cr)
      {
      char *output = new char [
        strlen(m_Makefile->GetStartOutputDirectory()) + 
        strlen(libName) + 30];
      sprintf(output,"%s/%s_force_%i",
              m_Makefile->GetStartOutputDirectory(),
              libName, count);
      const char* no_main_dependency = 0;
      const char* no_comment = 0;
      m_Makefile->AddCustomCommandToOutput(output,
                                           cr->GetDepends(),
                                           no_main_dependency,
                                           cr->GetCommandLines(),
                                           no_comment);
      cmSourceFile* outsf = 
        m_Makefile->GetSourceFileWithOutput(output);
      target.GetSourceFiles().push_back(outsf);
