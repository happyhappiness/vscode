    switch (cmsysProcess_GetState(cp)) {
      case cmsysProcess_State_Exited: {
        int v = cmsysProcess_GetExitValue(cp);
        char buf[100];
        sprintf(buf, "%d", v);
        this->Makefile->AddDefinition(result_variable, buf);
      } break;
