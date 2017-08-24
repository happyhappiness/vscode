(last) {
        this->AddFile(this->Internals->Files, realname);
      } else {
        this->ProcessDirectory(start + 1, realname, messages);
      }