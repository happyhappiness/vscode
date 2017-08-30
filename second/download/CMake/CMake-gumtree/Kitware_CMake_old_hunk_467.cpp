

    gg->CreateGenerationObjects();

    cmLocalGenerator* lg = gg->LocalGenerators[0];

    std::string includeFlags = lg->GetIncludeFlags(includeDirs, 0, language);



    std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");

    printf("%s %s\n", includeFlags.c_str(), definitions.c_str());

