    {
    char name[128];
    sprintf(name, "CMAKE_MATCH_%d", i);
    mf->AddDefinition(name, "");
    mf->MarkVariableAsUsed(name);
    }
}

