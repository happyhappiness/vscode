void cmGraphVizWriter::WriteGlobalFile(const char* fileName)
{
  cmGeneratedFileStream str(fileName);
  if ( !str )
    {
    return;
    }
  this->WriteHeader(str);

  fprintf(stderr, "Writing %s...\n", fileName);
  std::set<std::string> insertedConnections;
  std::set<std::string> insertedNodes;

  for(std::map<cmStdString, const cmTarget*>::const_iterator ptrIt =
                                                      this->TargetPtrs.begin();
      ptrIt != this->TargetPtrs.end();
      ++ptrIt)
    {
    if (ptrIt->second == NULL)
      {
      continue;
      }

    if (this->GenerateForTargetType(ptrIt->second->GetType()) == false)
      {
      continue;
      }

    this->WriteConnections(ptrIt->first.c_str(),
                              insertedNodes, insertedConnections, str);
    }
  this->WriteFooter(str);
}