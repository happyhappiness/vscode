fprintf(stderr, "static regex matched [%s] [%s] [%s]\n",
            this->ExtractStaticLibraryName.match(1).c_str(),
            this->ExtractStaticLibraryName.match(2).c_str(),
            this->ExtractStaticLibraryName.match(3).c_str())