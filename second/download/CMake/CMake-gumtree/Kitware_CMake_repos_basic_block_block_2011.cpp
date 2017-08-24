{
    *searchPos = '\0';
    source += currentPos;
    currentPos = searchPos + replaceSize;
    // replace
    source += with;
    searchPos = strstr(currentPos, replace);
  }