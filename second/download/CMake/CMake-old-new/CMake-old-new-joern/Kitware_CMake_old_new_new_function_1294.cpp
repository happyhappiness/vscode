void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout, 
                                 const char *libName,
                                 cmTarget &target)
{
  // if we should add regen rule then...
  const char *suppRegenRule = 
    m_Makefile->GetDefinition("CMAKE_SUPPRESS_REGENERATION");
  if (!cmSystemTools::IsOn(suppRegenRule))
    {
    this->AddDSPBuildRule();
    }

  // For utility targets need custom command since pre- and post-
  // build does not do anything in Visual Studio 6.  In order for the
  // rules to run in the correct order as custom commands, we need
  // special care for dependencies.  The first rule must depend on all
  // the dependencies of all the rules.  The later rules must each
  // depend only on the previous rule.
  if (target.GetType() == cmTarget::UTILITY &&
      (!target.GetPreBuildCommands().empty() ||
       !target.GetPostBuildCommands().empty()))
    {
    // Accumulate the dependencies of all the commands.
    std::vector<std::string> depends;
    for (std::vector<cmCustomCommand>::const_iterator cr =
           target.GetPreBuildCommands().begin();
         cr != target.GetPreBuildCommands().end(); ++cr)
      {
      depends.insert(depends.end(),
                     cr->GetDepends().begin(), cr->GetDepends().end());
      }
    for (std::vector<cmCustomCommand>::const_iterator cr =
           target.GetPostBuildCommands().begin();
         cr != target.GetPostBuildCommands().end(); ++cr)
      {
      depends.insert(depends.end(),
                     cr->GetDepends().begin(), cr->GetDepends().end());
      }

    // Add the pre- and post-build commands in order.
    int count = 1;
    for (std::vector<cmCustomCommand>::const_iterator cr =
           target.GetPreBuildCommands().begin();
         cr != target.GetPreBuildCommands().end(); ++cr)
      {
      this->AddUtilityCommandHack(target, count++, depends,
                                  cr->GetCommandLines());
      }
    for (std::vector<cmCustomCommand>::const_iterator cr =
           target.GetPostBuildCommands().begin();
         cr != target.GetPostBuildCommands().end(); ++cr)
      {
      this->AddUtilityCommandHack(target, count++, depends,
                                  cr->GetCommandLines());
      }
    }
  
  // trace the visual studio dependencies
  std::string name = libName;
  name += ".dsp.cmake";
  target.TraceVSDependencies(name, m_Makefile);

  // We may be modifying the source groups temporarily, so make a copy.
  std::vector<cmSourceGroup> sourceGroups = m_Makefile->GetSourceGroups();
  
  // get the classes from the source lists then add them to the groups
  std::vector<cmSourceFile*> & classes = target.GetSourceFiles();

  // now all of the source files have been properly assigned to the target
  // now stick them into source groups using the reg expressions
  for(std::vector<cmSourceFile*>::iterator i = classes.begin(); 
      i != classes.end(); i++)
    {
    // Add the file to the list of sources.
    std::string source = (*i)->GetFullPath();
    cmSourceGroup& sourceGroup = m_Makefile->FindSourceGroup(source.c_str(),
                                                             sourceGroups);
    sourceGroup.AssignSource(*i);
    // while we are at it, if it is a .rule file then for visual studio 6 we
    // must generate it
    if ((*i)->GetSourceExtension() == "rule")
      {
      if(!cmSystemTools::FileExists(source.c_str()))
        {
        cmSystemTools::ReplaceString(source, "$(IntDir)/", "");
#if defined(_WIN32) || defined(__CYGWIN__)
        std::ofstream fout(source.c_str(), 
                           std::ios::binary | std::ios::out | std::ios::trunc);
#else
        std::ofstream fout(source.c_str(), 
                           std::ios::out | std::ios::trunc);
#endif
        if(fout)
          {
          fout.write("# generated from CMake",22);
          fout.flush();
          fout.close();
          }
        }
      }
    }
  
  // Write the DSP file's header.
  this->WriteDSPHeader(fout, libName, target, sourceGroups);
  

  // Loop through every source group.
  for(std::vector<cmSourceGroup>::const_iterator sg = sourceGroups.begin();
      sg != sourceGroups.end(); ++sg)
    {
    const std::vector<const cmSourceFile *> &sourceFiles = 
      sg->GetSourceFiles();
    // If the group is empty, don't write it at all.
    if(sourceFiles.empty())
      { 
      continue; 
      }
    
    // If the group has a name, write the header.
    std::string name = sg->GetName();
    if(name != "")
      {
      this->WriteDSPBeginGroup(fout, name.c_str(), "");
      }
    
    // Loop through each source in the source group.
    for(std::vector<const cmSourceFile *>::const_iterator sf =
          sourceFiles.begin(); sf != sourceFiles.end(); ++sf)
      {
      std::string source = (*sf)->GetFullPath();
      const cmCustomCommand *command = 
        (*sf)->GetCustomCommand();
      std::string compileFlags;
      std::vector<std::string> depends;
      const char* cflags = (*sf)->GetProperty("COMPILE_FLAGS");
      if(cflags)
        {
        compileFlags = cflags;
        }
      const char* lang = 
        m_GlobalGenerator->GetLanguageFromExtension((*sf)->GetSourceExtension().c_str());
      if(lang && strcmp(lang, "CXX") == 0)
        {
        // force a C++ file type
        compileFlags += " /TP ";
        }
      
      // Check for extra object-file dependencies.
      const char* dependsValue = (*sf)->GetProperty("OBJECT_DEPENDS");
      if(dependsValue)
        {
        cmSystemTools::ExpandListArgument(dependsValue, depends);
        }
      if (source != libName || target.GetType() == cmTarget::UTILITY)
        {
        fout << "# Begin Source File\n\n";
        
        // Tell MS-Dev what the source is.  If the compiler knows how to
        // build it, then it will.
        fout << "SOURCE=" << 
          this->ConvertToOptionallyRelativeOutputPath(source.c_str()) << "\n\n";
        if(!depends.empty())
          {
          // Write out the dependencies for the rule.
          fout << "USERDEP__HACK=";
          for(std::vector<std::string>::const_iterator d = depends.begin();
              d != depends.end(); ++d)
            { 
            fout << "\\\n\t" << 
              this->ConvertToOptionallyRelativeOutputPath(d->c_str());
            }
          fout << "\n";
          }
        if (command)
          {
          std::string script =
            this->ConstructScript(command->GetCommandLines(), "\\\n\t");
          const char* comment = command->GetComment();
          const char* flags = compileFlags.size() ? compileFlags.c_str(): 0;
          this->WriteCustomRule(fout, source.c_str(), script.c_str(), 
                                (*comment?comment:"Custom Rule"),
                                command->GetDepends(), 
                                command->GetOutput(), flags);
          }
        else if(compileFlags.size())
          {
          for(std::vector<std::string>::iterator i
                = m_Configurations.begin(); i != m_Configurations.end(); ++i)
            { 
            if (i == m_Configurations.begin())
              {
              fout << "!IF  \"$(CFG)\" == " << i->c_str() << std::endl;
              }
            else 
              {
              fout << "!ELSEIF  \"$(CFG)\" == " << i->c_str() << std::endl;
              }
            fout << "\n# ADD CPP " << compileFlags << "\n\n";
            } 
          fout << "!ENDIF\n\n";
          }
        fout << "# End Source File\n";
        }
      }
    
    // If the group has a name, write the footer.
    if(name != "")
      {
      this->WriteDSPEndGroup(fout);
      }
    }  

  // Write the DSP file's footer.
  this->WriteDSPFooter(fout);
}