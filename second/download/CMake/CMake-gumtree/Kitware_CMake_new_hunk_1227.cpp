  char thirdLine[512]="";

  if (process)

    {

    sprintf(firstLine,

            "                                                               ");

    sprintf(secondLine,

            "                                                               ");

    sprintf(thirdLine,

            "                                                               ");

    }

  else

    {

    if (this->OkToGenerate)

      {

      sprintf(firstLine,

              "Press [c] to configure     Press [g] to generate and exit");

      }

    else

