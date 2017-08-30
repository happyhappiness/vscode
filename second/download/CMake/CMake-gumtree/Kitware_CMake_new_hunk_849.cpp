    cmSystemTools::ExpandListArgument(includes, includeDirs);



    std::string includeFlags = lg->GetIncludeFlags(includeDirs, 0,

                                                   language, false);



    std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");

    printf("%s %s\n", includeFlags.c_str(), definitions.c_str());

