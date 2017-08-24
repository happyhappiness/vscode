{
    const Value& childValue = value[index];
    isMultiLine =
        isMultiLine || ((childValue.isArray() || childValue.isObject()) &&
                        childValue.size() > 0);
  }