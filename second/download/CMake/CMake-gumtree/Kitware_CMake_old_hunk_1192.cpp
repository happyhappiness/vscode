    std::string includes = mf->GetSafeDefinition("PACKAGE_INCLUDE_DIRS");

    std::vector<std::string> includeDirs;

    cmSystemTools::ExpandListArgument(includes, includeDirs);

    for(std::vector<std::string>::const_iterator dirIt=includeDirs.begin();

            dirIt != includeDirs.end();

            ++dirIt)

      {

      mf->AddIncludeDirectory(dirIt->c_str(), false);

      }



    std::string includeFlags = lg->GetIncludeFlags(language.c_str(), false);

    std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");

    printf("%s %s\n", includeFlags.c_str(), definitions.c_str());

    }

