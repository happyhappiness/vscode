                           target.GetName().size() + 30)];
  sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
          target.GetName().c_str(), count);
  std::string comment = this->ConstructComment(origCommand, "<hack>");

  // Add the rule with the given dependencies and commands.
  std::string no_main_dependency = "";
  if(cmSourceFile* outsf =
     this->Makefile->AddCustomCommandToOutput(
       output, depends, no_main_dependency,
       origCommand.GetCommandLines(), comment.c_str(),
       origCommand.GetWorkingDirectory().c_str()))
    {
    target.AddSourceFile(outsf);
