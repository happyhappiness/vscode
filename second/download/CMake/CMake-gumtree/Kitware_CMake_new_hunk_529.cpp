                        const cmCustomCommand& origCommand)
{
  // Create a fake output that forces the rule to run.
  char* output = new char[(strlen(this->GetCurrentBinaryDirectory())
                           + target.GetName().size() + 30)];
  sprintf(output,"%s/%s_force_%i", this->GetCurrentBinaryDirectory(),
          target.GetName().c_str(), count);
  const char* comment = origCommand.GetComment();
  if(!comment && origCommand.GetOutputs().empty())
