    std::string linkLibs;
    std::string flags;
    std::string linkFlags;
    lg->GetTargetFlags(linkLibs, flags, linkFlags, *tgt);

    printf("%s\n", linkLibs.c_str() );

