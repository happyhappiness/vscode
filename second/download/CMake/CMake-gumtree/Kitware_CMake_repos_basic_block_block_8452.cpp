(int index = 0; index < size; ++index) {
      if (index > 0)
        document_ += ',';
      writeValue(value[index]);
    }