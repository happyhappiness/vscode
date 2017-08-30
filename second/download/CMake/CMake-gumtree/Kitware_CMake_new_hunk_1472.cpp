                           strlen(target.GetName()) + 30)];
  sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
          target.GetName(), count);
  std::string comment = this->ConstructComment(origCommand, "<hack>");

  // Add the rule with the given dependencies and commands.
  const char* no_main_dependency = 0;
  this->Makefile->AddCustomCommandToOutput(output,
                                       depends,
                                       no_main_dependency,
                                       origCommand.GetCommandLines(),
                                       comment.c_str(),
                                       origCommand.GetWorkingDirectory());

  // Replace the dependencies with the output of this rule so that the
