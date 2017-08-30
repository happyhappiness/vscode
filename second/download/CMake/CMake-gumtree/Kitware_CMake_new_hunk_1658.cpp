      cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
      }
    cres.m_Name = testname;
    if(m_TestsToRun.size() && 
       std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt) == m_TestsToRun.end())
      {
      continue;
      }

    if ( m_ShowOnly )
      {
      fprintf(stderr,"%3d/%3d Testing %-30s\n", cnt, (int)tmsize, testname.c_str());
