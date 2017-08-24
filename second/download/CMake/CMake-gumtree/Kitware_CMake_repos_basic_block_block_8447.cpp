(strpbrk(value, "\"\\\b\f\n\r\t") == NULL &&
      !containsControlCharacter(value))
    return std::string("\"") + value + "\"";