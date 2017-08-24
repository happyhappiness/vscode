#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
    fprintf(stderr, "Raw link item [%s]\n", this->RawLinkItems[i].c_str());
#endif
    if(cmSystemTools::FileIsFullPath(this->RawLinkItems[i].c_str()))
      {
      if(cmSystemTools::FileIsDirectory(this->RawLinkItems[i].c_str()))
        {
