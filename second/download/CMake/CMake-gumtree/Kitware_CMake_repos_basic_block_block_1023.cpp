{
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