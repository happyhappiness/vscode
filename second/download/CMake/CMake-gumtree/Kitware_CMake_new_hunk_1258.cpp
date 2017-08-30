  char buf[2048];

  const char *cwd = Getcwd(buf, sizeof(buf));



  std::cout << "Working directory: -->" << cwd << "<--";



  return 0;

}
