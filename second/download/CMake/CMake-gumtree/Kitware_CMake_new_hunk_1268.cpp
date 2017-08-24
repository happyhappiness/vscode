        {
        std::string tmp = (*d)->m_FullPath;
        std::string::size_type pos = tmp.rfind('.');
        if(pos != std::string::npos && (tmp.substr(pos) != ".h"))
          {
          tmp = tmp.substr(0, pos);
          fprintf(fout,"%s\n",(*d)->m_FullPath.c_str());
