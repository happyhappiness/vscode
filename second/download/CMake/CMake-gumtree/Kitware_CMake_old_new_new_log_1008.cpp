(name == "ADD_TEST")
        {
        if (this->m_UseRegExp && !var.find(args[0].c_str()))
          {
          continue;
          }
        fprintf(stderr,"Testing %-30s ",args[0].c_str());