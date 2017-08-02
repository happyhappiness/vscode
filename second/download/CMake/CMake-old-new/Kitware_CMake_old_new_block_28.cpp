{
        int v = cmsysProcess_GetExitValue(cp);
        char buf[100];
        sprintf(buf, "%d", v);
        this->Makefile->AddDefinition(result_variable, buf);
      }