      this->SetCurrentLinkType(LinkShared);

      this->LinkItems.push_back(this->ExtractSharedLibraryName.match(2));

      }

    else if(this->ExtractAnyLibraryName.find(*i))

      {

#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
