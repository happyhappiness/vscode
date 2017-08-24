  return this->GetCacheManager()->GetCacheValue(name);
}

int cmMakefile::DumpDocumentationToFile(std::ostream& f)
{
  // Open the supplied filename
  
  // Loop over all registered commands and print out documentation
  const char *name;
  const char *terse;
  const char *full;
  char tmp[1024];
  sprintf(tmp,"Version %d.%d", cmMakefile::GetMajorVersion(),
          cmMakefile::GetMinorVersion());
  f << "<html>\n";
  f << "<h1>Documentation for commands of CMake " << tmp << "</h1>\n";
  f << "<ul>\n";
  for(RegisteredCommandsMap::iterator j = m_Commands.begin();
      j != m_Commands.end(); ++j)
    {
    name = (*j).second->GetName();
    terse = (*j).second->GetTerseDocumentation();
    full = (*j).second->GetFullDocumentation();
    f << "<li><b>" << name << "</b> - " << terse << std::endl
      << "<br><i>Usage:</i> " << full << "</li>" << std::endl << std::endl;
    }
  f << "</ul></html>\n";
  return 1;
}


const char *cmMakefile::ExpandVariablesInString(std::string& source) const
