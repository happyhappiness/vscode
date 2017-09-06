void cmGraphVizWriter::WritePerTargetFiles(const char* fileName)
{
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

    std::set<std::string> insertedConnections;
    std::set<std::string> insertedNodes;

    std::string currentFilename = fileName;
    currentFilename += ".";
    currentFilename += ptrIt->first;
    cmGeneratedFileStream str(currentFilename.c_str());
    if ( !str )
      {
      return;
      }

    fprintf(stderr, "Writing %s...\n", currentFilename.c_str());
    this->WriteHeader(str);

    this->WriteConnections(ptrIt->first.c_str(),
                              insertedNodes, insertedConnections, str);
    this->WriteFooter(str);
    }

}