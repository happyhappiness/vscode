fprintf(stderr, "any regex matched [%s] [%s] [%s]\n",
            this->ExtractAnyLibraryName.match(1).c_str(),
            this->ExtractAnyLibraryName.match(2).c_str(),
            this->ExtractAnyLibraryName.match(3).c_str())