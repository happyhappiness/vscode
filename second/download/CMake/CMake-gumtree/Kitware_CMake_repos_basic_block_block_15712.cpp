{  
    int format_state = (names[names_index].format)(a);
    if (format_state == ARCHIVE_OK)
      return ((names[names_index].filter)(a));
    else
      return format_state;
  }