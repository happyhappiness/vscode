{
    std::string fname = dir + "/testRST.rst";
    std::ofstream fout(a_name.c_str());
    if (!fout) {
      std::cerr << "Could not open output " << a_name << std::endl;
      return 1;
    }

    cmRST r(fout, dir);
    if (!r.ProcessFile(fname)) {
      std::cerr << "Could not open input " << fname << std::endl;
      return 1;
    }
  }