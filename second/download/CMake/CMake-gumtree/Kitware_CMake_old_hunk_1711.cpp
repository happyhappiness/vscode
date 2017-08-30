    }



  std::string end_time = ::CurrentTime();

  char buffer[100];

  sprintf(buffer, "%.2f", percent_coverage);



  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"

      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"

      << "\t<LOC>" << total_lines << "</LOC>\n"

      << "\t<PercentCoverage>" << buffer << "</PercentCoverage>\n"

      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"

      << "</Coverage>\n"

      << "</Site>" << std::endl;



  std::cout << "\tCovered LOC:         " << total_tested << std::endl

            << "\tNot covered LOC:     " << total_untested << std::endl

            << "\tTotal LOC:           " << total_lines << std::endl

            << "\tPercentage Coverage: " << percent_coverage << "%" << std::endl;





  return 1;
