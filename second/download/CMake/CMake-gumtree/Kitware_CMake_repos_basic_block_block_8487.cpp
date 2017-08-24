(int index = 0; index < size; ++index) {
      writeValue(value[index]);
      lineLength += int(childValues_[index].length());
    }