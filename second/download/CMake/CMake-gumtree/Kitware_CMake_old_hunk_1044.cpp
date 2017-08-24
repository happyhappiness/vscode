  return this->CacheManager->GetCacheValue(name);
}

int cmake::DumpDocumentationToFile(std::ostream& f)
{
#ifdef CMAKE_BUILD_WITH_CMAKE
  // Loop over all registered commands and print out documentation
  const char *name;
  const char *terse;
  const char *full;
  char tmp[1024];
  sprintf(tmp,"Version %s", cmVersion::GetCMakeVersion());
  f << "<html>\n";
  f << "<h1>Documentation for commands of CMake " << tmp << "</h1>\n";
  f << "<ul>\n";
  for(RegisteredCommandsMap::iterator j = this->Commands.begin();
      j != this->Commands.end(); ++j)
    {
    name = (*j).second->GetName();
    terse = (*j).second->GetTerseDocumentation();
    full = (*j).second->GetFullDocumentation();
    f << "<li><b>" << name << "</b> - " << terse << std::endl
      << "<br><i>Usage:</i> " << full << "</li>" << std::endl << std::endl;
    }
  f << "</ul></html>\n";
#else
  (void)f;
#endif
  return 1;
}

void cmake::AddDefaultCommands()
{
  std::list<cmCommand*> commands;
