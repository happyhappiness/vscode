    {

    std::string reg_shared = reg;

    this->SharedRegexString =

      this->CreateExtensionRegex(this->SharedLinkExtensions);

    reg_shared += this->SharedRegexString;

#ifdef CM_COMPUTE_LINK_INFO_DEBUG

  fprintf(stderr, "shared regex [%s]\n", reg_shared.c_str());

