    total_untested += cov.m_UnTested;
    float cper = 0;
    float cmet = 0;
    if ( total_tested + total_untested > 0 )
      {
      cper = (100 * static_cast<float>(cov.m_Tested)/
        static_cast<float>(cov.m_Tested + cov.m_UnTested));
      cmet = ( static_cast<float>(cov.m_Tested + 10) /
        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));
      }
    char cmbuff[100];
    char cpbuff[100];
    sprintf(cmbuff, "%.2f", cmet);
    sprintf(cpbuff, "%.2f", cper);

    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
      << "\t\t<PercentCoverage>" << cpbuff << "</PercentCoverage>\n"
      << "\t\t<CoverageMetric>" << cmbuff << "</CoverageMetric>\n"
      << "\t</File>" << std::endl;
    ccount ++;
    }
