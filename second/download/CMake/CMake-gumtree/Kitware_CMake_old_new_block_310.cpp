r(std::vector<std::string>::iterator si = sources.begin();
        si != sources.end(); ++si)
      {
      fprintf(fout, " \"%s\"", si->c_str());

      // Add dependencies on any non-temporary sources.
      if(si->find("CMakeTmp") == si->npos)
        {
        this->Makefile->AddCMakeDependFile(*si);
        }
      }