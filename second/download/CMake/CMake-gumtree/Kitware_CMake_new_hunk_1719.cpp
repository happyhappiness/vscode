                  << "</Site>" << std::endl;
      cfileoutput.close();
      sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
      if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
        {
        std::cout << "Cannot open log file" << std::endl;
        return 1;
