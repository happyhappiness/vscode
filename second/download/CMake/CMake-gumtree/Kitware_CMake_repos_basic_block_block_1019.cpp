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
    // On Windows and apple, no difference between lower and upper case
    fname = kwsys::SystemTools::LowerCase(fname);
#endif

    bool isDir = kwsys::SystemTools::FileIsDirectory(realname);
    bool isSymLink = kwsys::SystemTools::FileIsSymlink(realname);

    if (isDir && (!isSymLink || this->RecurseThroughSymlinks)) {
      if (isSymLink) {
        ++this->FollowedSymlinkCount;
        std::string realPathErrorMessage;
        std::string canonicalPath(
          SystemTools::GetRealPath(dir, &realPathErrorMessage));

        if (!realPathErrorMessage.empty()) {
          if (messages) {
            messages->push_back(Message(
              Glob::error, "Canonical path generation from path '" + dir +
                "' failed! Reason: '" + realPathErrorMessage + "'"));
          }
          return false;
        }

        if (std::find(this->VisitedSymlinks.begin(),
                      this->VisitedSymlinks.end(),
                      canonicalPath) == this->VisitedSymlinks.end()) {
          if (this->RecurseListDirs) {
            // symlinks are treated as directories
            this->AddFile(this->Internals->Files, realname);
          }

          this->VisitedSymlinks.push_back(canonicalPath);
          if (!this->RecurseDirectory(start + 1, realname, messages)) {
            this->VisitedSymlinks.pop_back();

            return false;
          }
          this->VisitedSymlinks.pop_back();
        }
        // else we have already visited this symlink - prevent cyclic recursion
        else if (messages) {
          std::string message;
          for (std::vector<std::string>::const_iterator pathIt =
                 std::find(this->VisitedSymlinks.begin(),
                           this->VisitedSymlinks.end(), canonicalPath);
               pathIt != this->VisitedSymlinks.end(); ++pathIt) {
            message += *pathIt + "\n";
          }
          message += canonicalPath + "/" + fname;
          messages->push_back(Message(Glob::cyclicRecursion, message));
        }
      } else {
        if (this->RecurseListDirs) {
          this->AddFile(this->Internals->Files, realname);
        }
        if (!this->RecurseDirectory(start + 1, realname, messages)) {
          return false;
        }
      }
    } else {
      if (!this->Internals->Expressions.empty() &&
          this->Internals->Expressions.rbegin()->find(fname)) {
        this->AddFile(this->Internals->Files, realname);
      }
    }
  }