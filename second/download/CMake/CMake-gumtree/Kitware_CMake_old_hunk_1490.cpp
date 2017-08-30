  // add info to the visited set

  visited->insert(info);

  // now recurse with info's dependencies

  for(cmDependInformation::DependencySet::const_iterator d = 

        info->m_DependencySet.begin();

      d != info->m_DependencySet.end(); ++d)

    {

    if (visited->find(*d) == visited->end())

      {

      if(info->m_FullPath != "")

        {

        std::string tmp = (*d)->m_FullPath;

        std::string::size_type pos = tmp.rfind('.');

        if(pos != std::string::npos && (tmp.substr(pos) != ".h"))

          {

          tmp = tmp.substr(0, pos);

          fprintf(fout,"%s\n",(*d)->m_FullPath.c_str());

          }

        }

      this->ListDependencies(*d,fout,visited);

