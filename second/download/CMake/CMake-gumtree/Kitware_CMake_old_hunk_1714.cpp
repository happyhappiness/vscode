    }



  std::string end_time = ::CurrentTime();



  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"

      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"

      << "\t<LOC>" << total_lines << "</LOC>\n"

      << "\t<PercentCoverage>" << percent_coverage << "</PercentCoverage>\n"

      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"

      << "</Coverage>\n"

      << "</Site>" << std::endl;
