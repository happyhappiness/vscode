f(this->ExtractAnyLibraryName.find(*i))
      {
#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
      fprintf(stderr, "any regex matched [%s] [%s] [%s]\n",
              this->ExtractAnyLibraryName.match(1).c_str(),
              this->ExtractAnyLibraryName.match(2).c_str(),
              this->ExtractAnyLibraryName.match(3).c_str());
#endif
      this->SetCurrentLinkType(this->StartLinkType);
      this->LinkItems.push_back(this->ExtractAnyLibraryName.match(2));
      }