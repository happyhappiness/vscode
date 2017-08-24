{
      /* There might be a zone identifier */
      if(strncmp("%25", ptr, 3))
        infof(data, "Please URL encode %% as %%25, see RFC 6874.\n");
      ptr++;
      /* Allow unreserved characters as defined in RFC 3986 */
      while(*ptr && (ISALPHA(*ptr) || ISXDIGIT(*ptr) || (*ptr == '-') ||
                     (*ptr == '.') || (*ptr == '_') || (*ptr == '~')))
        ptr++;
    }