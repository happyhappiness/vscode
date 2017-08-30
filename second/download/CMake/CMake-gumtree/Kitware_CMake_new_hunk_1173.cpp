    std::string linkLibs;

    std::string flags;

    std::string linkFlags;

    cmGeneratorTarget gtgt(tgt);

    lg->GetTargetFlags(linkLibs, flags, linkFlags, &gtgt);



    printf("%s\n", linkLibs.c_str() );



