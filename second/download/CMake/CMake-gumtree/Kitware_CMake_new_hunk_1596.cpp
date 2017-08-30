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

  

