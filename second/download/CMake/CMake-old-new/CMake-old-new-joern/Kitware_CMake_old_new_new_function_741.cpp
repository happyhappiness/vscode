void
cmLocalVisualStudio6Generator
::AddUtilityCommandHack(cmTarget& target, int count,
                        std::vector<std::string>& depends,
                        const cmCustomCommand& origCommand)
{
  // Create a fake output that forces the rule to run.
  char* output = new char[(strlen(this->Makefile->GetStartOutputDirectory()) +
                           target.GetName().size() + 30)];
  sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
          target.GetName().c_str(), count);
  std::string comment = this->ConstructComment(origCommand, "<hack>");

  // Add the rule with the given dependencies and commands.
  const char* no_main_dependency = 0;
  if(cmSourceFile* outsf =
     this->Makefile->AddCustomCommandToOutput(
       output, depends, no_main_dependency,
       origCommand.GetCommandLines(), comment.c_str(),
       origCommand.GetWorkingDirectory()))
    {
    target.AddSourceFile(outsf);
    }

  // Replace the dependencies with the output of this rule so that the
  // next rule added will run after this one.
  depends.clear();
  depends.push_back(output);

  // Free the fake output name.
  delete [] output;
}