    }

  std::string end_time = ::CurrentTime();

  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
      << "\t<LOC>" << total_lines << "</LOC>\n"
      << "\t<PercentCoverage>";
  log.setf(std::ios::fixed, std::ios::floatfield);
  log.precision(2);
  log << FIXNUM(percent_coverage)<< "</PercentCoverage>\n"
      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
      << "</Coverage>\n"
      << "</Site>" << std::endl;

  std::cout << "\tCovered LOC:         " << total_tested << std::endl
            << "\tNot covered LOC:     " << total_untested << std::endl
            << "\tTotal LOC:           " << total_lines << std::endl
            << "\tPercentage Coverage: ";

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout.precision(2);
  std::cout << FIXNUM(percent_coverage) << "%" << std::endl;


  return 1;