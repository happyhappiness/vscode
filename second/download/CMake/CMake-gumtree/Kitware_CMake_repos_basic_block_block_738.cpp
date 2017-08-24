{
    // Found the included file.  Save it in the set of included files.
    parser->Info.Includes.insert(fullName);

    // Parse it immediately to translate the source inline.
    cmFortranParser_FilePush(parser, fullName.c_str());
  }