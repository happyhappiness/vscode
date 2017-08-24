(first != end) {
      /* Store the end of this path entry.  */
      const char* last;

      /* Skip all path separators.  */
      for (; *first && *first == KWSYS_SHARED_FORWARD_PATH_SEP; ++first)
        ;

      /* Find the next separator.  */
      for (last = first; *last && *last != KWSYS_SHARED_FORWARD_PATH_SEP;
           ++last)
        ;

      /* If we got a non-empty directory, look for the executable there.  */
      if (first < last) {
        /* Determine the length without trailing slash.  */
        size_t length = (size_t)(last - first);
        if (*(last - 1) == '/' || *(last - 1) == '\\') {
          --length;
        }

        /* Construct the name of the executable in this location.  */
        strncpy(result, first, length);
        result[length] = KWSYS_SHARED_FORWARD_PATH_SLASH;
        strcpy(result + (length) + 1, argv0);

        /* Check if it exists and is executable.  */
        if (kwsys_shared_forward_is_executable(result)) {
          /* Found it.  */
          result[length] = 0;
          return 1;
        }
      }

      /* Move to the next directory in the path.  */
      first = last;
    }