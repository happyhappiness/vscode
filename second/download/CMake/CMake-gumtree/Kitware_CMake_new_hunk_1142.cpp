#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
    fprintf(stderr, "Raw link item [%s]\n", this->RawLinkItems[i].c_str());
#endif
    // check to see if the file is a full path or just contains 
    // a / in it and is a path to something
    if(cmSystemTools::FileIsFullPath(this->RawLinkItems[i].c_str())
      || this->RawLinkItems[i].find("/") != cmStdString.npos)
      {
      if(cmSystemTools::FileIsDirectory(this->RawLinkItems[i].c_str()))
        {
