{
    std::string e_line;
    std::string a_line;
    bool e_eol;
    bool a_eol;
    e_ret = cmSystemTools::GetLineFromStream(e_fin, e_line, &e_eol);
    a_ret = cmSystemTools::GetLineFromStream(a_fin, a_line, &a_eol);
    ++lineno;
    if (e_ret != a_ret || e_line != a_line || e_eol != a_eol) {
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
  }