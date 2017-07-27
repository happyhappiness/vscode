fprintf(stderr, "shared regex matched [%s] [%s] [%s]\n",
            this->ExtractSharedLibraryName.match(1).c_str(),
            this->ExtractSharedLibraryName.match(2).c_str(),
            this->ExtractSharedLibraryName.match(3).c_str())