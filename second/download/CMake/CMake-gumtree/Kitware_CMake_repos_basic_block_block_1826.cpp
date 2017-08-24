(buffer[i] != ' ' && buffer[i] != '\t') {
          return this->ExtractValueFromCpuInfoFile(buffer, word, pos2);
        }