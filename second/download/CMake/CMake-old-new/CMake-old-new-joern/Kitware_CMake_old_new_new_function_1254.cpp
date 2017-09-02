void cmOutputRequiredFilesCommand::
ListDependencies(cmDependInformation const *info,
                 FILE *fout,
                 std::set<cmDependInformation const*> *visited)
{
  // add info to the visited set
  visited->insert(info);
  // now recurse with info's dependencies
  for(cmDependInformation::DependencySetType::const_iterator d = 
        info->DependencySet.begin();
      d != info->DependencySet.end(); ++d)
    {
    if (visited->find(*d) == visited->end())
      {
      if(info->FullPath != "")
        {
        std::string tmp = (*d)->FullPath;
        std::string::size_type pos = tmp.rfind('.');
        if(pos != std::string::npos && (tmp.substr(pos) != ".h"))
          {
          tmp = tmp.substr(0, pos);
          fprintf(fout,"%s\n",(*d)->FullPath.c_str());
          }
        }
      this->ListDependencies(*d,fout,visited);
      }
    }
}