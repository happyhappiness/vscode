(this->RecurseListDirs) {
            // symlinks are treated as directories
            this->AddFile(this->Internals->Files, realname);
          }