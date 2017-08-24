{
      a_fin.seekg(0, std::ios::beg);
      std::cerr << "Actual output does not match that expected on line "
                << lineno << "." << std::endl
                << "Expected ";
      reportLine(std::cerr, e_ret, e_line, e_eol);
      std::cerr << " but got ";
      reportLine(std::cerr, a_ret, a_line, a_eol);
      std::cerr << "." << std::endl
                << "Actual output:" << std::endl
                << a_fin.rdbuf();
      return 1;
    }