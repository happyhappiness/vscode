(std::find(this->VisitedSymlinks.begin(),
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