{
    childValues_.reserve(size);
    addChildValues_ = true;
    int lineLength = 4 + (size - 1) * 2; // '[ ' + ', '*n + ' ]'
    for (int index = 0; index < size; ++index) {
      writeValue(value[index]);
      lineLength += int(childValues_[index].length());
    }
    addChildValues_ = false;
    isMultiLine = isMultiLine || lineLength >= rightMargin_;
  }