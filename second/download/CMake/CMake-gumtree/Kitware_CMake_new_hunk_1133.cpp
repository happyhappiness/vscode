  if(!this->StaticLinkExtensions.empty())

    {

    std::string reg_static = reg;

    reg_static += this->CreateExtensionRegex(this->StaticLinkExtensions,

                                             LinkStatic);

#ifdef CM_COMPUTE_LINK_INFO_DEBUG

  fprintf(stderr, "static regex [%s]\n", reg_static.c_str());

#endif

