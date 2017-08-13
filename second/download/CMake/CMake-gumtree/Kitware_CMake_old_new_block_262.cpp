{
  // Create a fake output that forces the rule to run.
  char* output = new char[(strlen(this->Makefile->GetCurrentBinaryDirectory())
                           + target.GetName().size() + 30)];
  sprintf(output,"%s/%s_force_%i", this->Makefile->GetCurrentBinaryDirectory(),
          target.GetName().c_str(), count);
  const char* comment = origCommand.GetComment();
  if(!comment && origCommand.GetOutputs().empty())
    {
    comment = "<hack>";
    }

  // Add the rule with the given dependencies and commands.
  std::string no_main_dependency = "";
  if(cmSourceFile* outsf =
     this->Makefile->AddCustomCommandToOutput(
       output, depends, no_main_dependency,
       origCommand.GetCommandLines(), comment,
       origCommand.GetWorkingDirectory().c_str()))
    {
    cmGeneratorTarget* gt = this->GlobalGenerator->GetGeneratorTarget(&target);
    gt->AddSource(outsf->GetFullPath());
    }

  // Replace the dependencies with the output of this rule so that the
  // next rule added will run after this one.
  depends.clear();
  depends.push_back(output);

  // Free the fake output name.
  delete [] output;
}