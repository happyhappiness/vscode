{
  // std::cout << "ProcessDirectory: " << dir << std::endl;
  bool last = (start == this->Internals->Expressions.size() - 1);
  if (last && this->Recurse) {
    this->RecurseDirectory(start, dir, messages);
    return;
  }

  if (start >= this->Internals->Expressions.size()) {
    return;
  }

  kwsys::Directory d;
  if (!d.Load(dir)) {
    return;
  }
  unsigned long cc;
  std::string realname;
  std::string fname;
  for (cc = 0; cc < d.GetNumberOfFiles(); cc++) {
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
}