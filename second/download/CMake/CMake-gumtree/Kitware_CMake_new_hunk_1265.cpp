    char name[128];

    sprintf(name, "CMAKE_MATCH_%d", i);

    mf->AddDefinition(name, re.match(i).c_str());

    mf->MarkVariableAsUsed(name);

    }

}


