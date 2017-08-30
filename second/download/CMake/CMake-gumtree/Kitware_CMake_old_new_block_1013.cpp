{
    if (this->OkToGenerate)
      {
      sprintf(firstLine,
              "Press [c] to configure     Press [g] to generate and exit");
      }
    else
      {
      sprintf(firstLine,  "Press [c] to configure                                   ");
      }
    if (this->AdvancedMode)
      {
      sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently On)");
      }
    else
      {
      sprintf(thirdLine,  "Press [t] to toggle advanced mode (Currently Off)");
      }

    sprintf(secondLine,
            "Press [h] for help         Press [q] to quit without generating");
    }