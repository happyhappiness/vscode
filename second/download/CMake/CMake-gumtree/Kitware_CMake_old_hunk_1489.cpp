                        const cmCustomCommand& origCommand)

{

  // Create a fake output that forces the rule to run.

  char* output = new char[(strlen(m_Makefile->GetStartOutputDirectory()) +

                           strlen(target.GetName()) + 30)];

  sprintf(output,"%s/%s_force_%i", m_Makefile->GetStartOutputDirectory(),

          target.GetName(), count);



  // Add the rule with the given dependencies and commands.

  const char* no_main_dependency = 0;

  m_Makefile->AddCustomCommandToOutput(output,

                                       depends,

                                       no_main_dependency,

                                       origCommand.GetCommandLines(),

