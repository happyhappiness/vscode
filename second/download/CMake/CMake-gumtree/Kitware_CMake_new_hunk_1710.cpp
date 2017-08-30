    total_untested += cov.m_UnTested;

    float cper = 0;

    float cmet = 0;

    if ( total_tested + total_untested > 0 && (cov.m_Tested + cov.m_UnTested) > 0)

      {

      cper = (100 * static_cast<float>(cov.m_Tested)/

        static_cast<float>(cov.m_Tested + cov.m_UnTested));

      cmet = ( static_cast<float>(cov.m_Tested + 10) /

        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));

      }



    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath

      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"

      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"

      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"

      << "\t\t<PercentCoverage>";

    log.setf(std::ios::fixed, std::ios::floatfield);

    log.precision(2);

    log << FIXNUM(cper) << "</PercentCoverage>\n"

      << "\t\t<CoverageMetric>";

    log.setf(std::ios::fixed, std::ios::floatfield);

    log.precision(2);

    log << FIXNUM(cmet) << "</CoverageMetric>\n"

      << "\t</File>" << std::endl;

    ccount ++;

    }

