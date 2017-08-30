    langFlags += "_FLAGS";

    fprintf(fout, "SET(CMAKE_VERBOSE_MAKEFILE 1)\n");

    fprintf(fout, "SET(CMAKE_%s_FLAGS \"", lang);

    const char* flags = this->Makefile->GetDefinition(langFlags.c_str());

    if(flags)

      {

      fprintf(fout, " %s ", flags);

