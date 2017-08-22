{
  // Create a fake output that forces the rule to run.
  char* output = new char[(strlen(this->Makefile->GetStartOutputDirectory()) +
                           strlen(target.GetName()) + 30)];
  sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
          target.GetName(), count);
  std::string comment = this->ConstructComment(origCommand, "<hack>");

  // Add the rule with the given dependencies and commands.
