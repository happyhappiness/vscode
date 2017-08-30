    std::string includes = mf->GetSafeDefinition("PACKAGE_INCLUDE_DIRS");

    std::vector<std::string> includeDirs;

    cmSystemTools::ExpandListArgument(includes, includeDirs);



    std::string includeFlags = lg->GetIncludeFlags(includeDirs,

                                                   language.c_str(), false);



    std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");

    printf("%s %s\n", includeFlags.c_str(), definitions.c_str());

    }

