
    gg->CreateGenerationObjects();
    cmLocalGenerator* lg = gg->LocalGenerators[0];
    std::string includeFlags =
      lg->GetIncludeFlags(includeDirs, CM_NULLPTR, language);

    std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");
    printf("%s %s\n", includeFlags.c_str(), definitions.c_str());
