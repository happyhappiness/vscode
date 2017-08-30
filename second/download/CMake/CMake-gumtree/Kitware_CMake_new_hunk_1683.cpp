
        if ( !m_ShowOnly )
          {
          if (res == cmsysProcess_State_Exited && retVal == 0)
            {
            fprintf(stderr,"   Passed\n");
            passed.push_back(args[0].Value); 
