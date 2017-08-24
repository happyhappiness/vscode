(std::vector<std::string>::const_iterator pathIt =
                 std::find(this->VisitedSymlinks.begin(),
                           this->VisitedSymlinks.end(), canonicalPath);
               pathIt != this->VisitedSymlinks.end(); ++pathIt) {
            message += *pathIt + "\n";
          }