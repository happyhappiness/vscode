//    }

//  else

//    {

  char firstLine[512]="";

  char secondLine[512]="";

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

    if (m_OkToGenerate)

      {

      sprintf(firstLine,  

              "Press [c] to configure     Press [g] to generate and exit");

      }

    else

      {

