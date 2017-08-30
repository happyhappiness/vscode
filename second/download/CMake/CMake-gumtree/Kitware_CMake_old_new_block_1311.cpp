{
      sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
      std::cout << "Open file: " << cfileoutputname << std::endl;
      if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
                                   cfileoutputname, cfileoutput))
        {
        std::cerr << "Cannot open log file: " << cfileoutputname << std::endl;
        return 1;
        }
      local_start_time = m_CTest->CurrentTime();
      m_CTest->StartXML(cfileoutput);
      cfileoutput << "<CoverageLog>\n"
        << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
      }