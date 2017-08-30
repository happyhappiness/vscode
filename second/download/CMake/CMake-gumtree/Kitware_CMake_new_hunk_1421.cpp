      this->SetCurrentLinkType(LinkShared);

      this->LinkItems.push_back(this->ExtractSharedLibraryName.match(2));

      }

    else if(this->ExtractStaticLibraryName.find(*i))

      {

#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG

      fprintf(stderr, "static regex matched [%s] [%s] [%s]\n",

              this->ExtractStaticLibraryName.match(1).c_str(),

              this->ExtractStaticLibraryName.match(2).c_str(),

              this->ExtractStaticLibraryName.match(3).c_str());

#endif

      this->SetCurrentLinkType(LinkStatic);

      this->LinkItems.push_back(this->ExtractStaticLibraryName.match(2));

      }

    else if(this->ExtractAnyLibraryName.find(*i))

      {

#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
