void cmOrderLinkDirectories::PrepareLinkTargets()
{
  std::vector<cmStdString> originalLinkItems = this->LinkItems;
  this->LinkItems.clear();
  this->CurrentLinkType = this->StartLinkType;
  for(std::vector<cmStdString>::iterator i = originalLinkItems.begin();
      i != originalLinkItems.end(); ++i)
    {
    // separate the library name from libfoo.a or foo.a
    if(this->ExtractStaticLibraryName.find(*i))
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
    else if(this->ExtractSharedLibraryName.find(*i))
      {
#ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
      fprintf(stderr, "shared regex matched [%s] [%s] [%s]\n",
              this->ExtractSharedLibraryName.match(1).c_str(),
              this->ExtractSharedLibraryName.match(2).c_str(),
              this->ExtractSharedLibraryName.match(3).c_str());
#endif
      this->SetCurrentLinkType(LinkShared);
      this->LinkItems.push_back(this->ExtractSharedLibraryName.match(2));
      }
    else if(this->ExtractAnyLibraryName.find(*i))
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
    else
      {
      this->SetCurrentLinkType(this->StartLinkType);
      this->LinkItems.push_back(*i);
      }
    }

  // Restore the original linking type so system runtime libraries are
  // linked properly.
  this->SetCurrentLinkType(this->StartLinkType);
}