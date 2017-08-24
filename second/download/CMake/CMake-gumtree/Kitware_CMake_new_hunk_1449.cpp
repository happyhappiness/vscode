        errorwarning.m_PreContext += lines[jj] + "\n";
        }
      for ( jj = kk+1; 
            jj < lines.size() && jj < kk + 7 /* && markedLines[jj] == 0*/; 
            jj ++ )
        {
        errorwarning.m_PostContext += lines[jj] + "\n";
        }
      errorsWarnings.push_back(errorwarning);
      }
    }
  std::string testingDir = m_ToplevelPath + "/Testing/CDart";
  if ( cmSystemTools::FileExists(testingDir.c_str()) )
    {
    if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
      {
      std::cerr << "File " << testingDir 
                << " is in the place of the testing directory"
                << std::endl;
      return 1;
      }
    }
  else
    {
    if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
      {
      std::cerr << "Cannot create directory " << testingDir
                << std::endl;
      return 1;
      }
    }
  std::string buildxml = testingDir + "/Build.xml";
  std::ofstream ofs(buildxml.c_str());
  if( !ofs )
    {
    std::cerr << "Cannot create build XML file" << std::endl;
    return 1;
    }
  this->GenerateDartBuildOutput(ofs, errorsWarnings);
  return 0;
}


void ctest::GenerateDartBuildOutput(std::ostream& os, 
                                    std::vector<cmCTestBuildErrorWarning> ew)
{
  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
     << "\" BuildStamp=\"" << m_CurrentTag << "-Experimental\" Name=\""
     << m_DartConfiguration["Site"] << "\">\n"
     << "<Build>\n"
     << "  <StartDateTime>" << m_StartBuild << "</StartDateTime>\n"
     << "  <BuildCommand>" << m_DartConfiguration["MakeCommand"]
     << "</BuildCommand>" << std::endl;
    
