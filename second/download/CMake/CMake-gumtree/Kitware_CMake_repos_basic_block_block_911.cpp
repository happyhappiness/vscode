(arg.size() == sarg.size() || arg.at(sarg.size()) != '=') {
            this->Internals->LastArgument--;
            return 0;
          }