                        const cmCustomCommand& origCommand)
{
  // Create a fake output that forces the rule to run.
  char* output = new char[(strlen(this->Makefile->GetStartOutputDirectory()) +
                           strlen(target.GetName()) + 30)];
  sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
          target.GetName(), count);

  // Add the rule with the given dependencies and commands.
  const char* no_main_dependency = 0;
  this->Makefile->AddCustomCommandToOutput(output,
                                       depends,
                                       no_main_dependency,
                                       origCommand.GetCommandLines(),
