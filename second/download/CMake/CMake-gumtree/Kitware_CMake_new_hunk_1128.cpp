    {

    char name[128];

    sprintf(name, "CMAKE_MATCH_%d", i);

    const char* s = mf->GetDefinition(name);

    if(s && *s != 0)

      {

      mf->AddDefinition(name, "");

      mf->MarkVariableAsUsed(name);

      }

    }

}



