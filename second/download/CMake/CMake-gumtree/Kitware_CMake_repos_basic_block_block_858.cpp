(first < last) {
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