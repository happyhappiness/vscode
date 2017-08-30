                           target.GetName().size() + 30)];

  sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),

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

    target.AddSourceFile(outsf);

