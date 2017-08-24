(!this->Internals->Expressions.empty() &&
          this->Internals->Expressions.rbegin()->find(fname)) {
        this->AddFile(this->Internals->Files, realname);
      }