      {
      local_end_time = ::CurrentTime();
      cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
        << "</CoverageLog>\n"
        << "</Site>" << std::endl;
      cfileoutput.close();
      std::cout << "Close file: " << cfileoutputname << std::endl;
      ccount = 0;
      }
    if ( ccount == 0 )
      {
      sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
      std::cout << "Open file: " << cfileoutputname << std::endl;
      if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
        {
        std::cout << "Cannot open log file: " << cfileoutputname << std::endl;
        return 1;
        }
      local_start_time = ::CurrentTime();
      cfileoutput << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
        << "\" BuildStamp=\"" << m_CurrentTag << "-"
        << this->GetTestModelString() << "\" Site=\""
        << m_DartConfiguration["Site"] << "\">\n"
        << "<CoverageLog>\n"
        << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
      }

    //std::cerr << "Final process of Source file: " << cit->first << std::endl;
