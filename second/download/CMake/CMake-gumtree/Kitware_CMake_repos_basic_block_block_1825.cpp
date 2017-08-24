(size_t i = this->CurrentPositionInFile + strlen(word); i < pos;
           ++i) {
        if (buffer[i] != ' ' && buffer[i] != '\t') {
          return this->ExtractValueFromCpuInfoFile(buffer, word, pos2);
        }
      }