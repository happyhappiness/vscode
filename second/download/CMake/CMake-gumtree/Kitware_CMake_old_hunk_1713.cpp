      cmet = ( static_cast<float>(cov.m_Tested + 10) /

        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));

      }

    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath

      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"

      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"

      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"

      << "\t\t<PercentCoverage>" << cper << "</PercentCoverage>\n"

      << "\t\t<CoverageMetric>" << cmet << "</CoverageMetric>\n"

      << "\t</File>" << std::endl;

    ccount ++;

    }

