(cc = 0; cc < d.GetNumberOfFiles(); cc++) {
    fname = d.GetFile(cc);
    if (fname == "." || fname == "..") {
      continue;
    }

    if (start == 0) {
      realname = dir + fname;
    } else {
      realname = dir + "/" + fname;
    }

#if defined(KWSYS_GLOB_CASE_INDEPENDENT)
    // On case-insensitive file systems convert to lower case for matching.
    fname = kwsys::SystemTools::LowerCase(fname);
#endif

    // std::cout << "Look at file: " << fname << std::endl;
    // std::cout << "Match: "
    // << this->Internals->TextExpressions[start].c_str() << std::endl;
    // std::cout << "Real name: " << realname << std::endl;

    if ((!last && !kwsys::SystemTools::FileIsDirectory(realname)) ||
        (!this->ListDirs && last &&
         kwsys::SystemTools::FileIsDirectory(realname))) {
      continue;
    }

    if (this->Internals->Expressions[start].find(fname)) {
      if (last) {
        this->AddFile(this->Internals->Files, realname);
      } else {
        this->ProcessDirectory(start + 1, realname, messages);
      }
    }
  }