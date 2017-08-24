{
    /* Only one leading drive letter and slash.  */
    strncpy(result, begin, (size_t)last_slash_index);
    result[last_slash_index] = KWSYS_SHARED_FORWARD_PATH_SLASH;
    result[last_slash_index + 1] = 0;
  }