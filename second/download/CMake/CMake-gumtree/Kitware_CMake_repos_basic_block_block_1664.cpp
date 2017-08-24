(in_escape) {
      /* This character is escaped so do no special handling.  */
      if (!in_argument) {
        in_argument = 1;
      }
      if (!kwsysSystem__AppendByte(local_buffer, &buffer_begin, &buffer_end,
                                   &buffer_size, *c)) {
        failed = 1;
        break;
      }
      in_escape = 0;
    } else if (*c == '\\') {
      /* The next character should be escaped.  */
      in_escape = 1;
    } else if (*c == '\'' && !in_double) {
      /* Enter or exit single-quote state.  */
      if (in_single) {
        in_single = 0;
      } else {
        in_single = 1;
        if (!in_argument) {
          in_argument = 1;
        }
      }
    } else if (*c == '"' && !in_single) {
      /* Enter or exit double-quote state.  */
      if (in_double) {
        in_double = 0;
      } else {
        in_double = 1;
        if (!in_argument) {
          in_argument = 1;
        }
      }
    } else if (isspace((unsigned char)*c)) {
      if (in_argument) {
        if (in_single || in_double) {
          /* This space belongs to a quoted argument.  */
          if (!kwsysSystem__AppendByte(local_buffer, &buffer_begin,
                                       &buffer_end, &buffer_size, *c)) {
            failed = 1;
            break;
          }
        } else {
          /* This argument has been terminated by whitespace.  */
          if (!kwsysSystem__AppendArgument(
                local_pointers, &pointer_begin, &pointer_end, &pointers_size,
                local_buffer, &buffer_begin, &buffer_end, &buffer_size)) {
            failed = 1;
            break;
          }
          in_argument = 0;
        }
      }
    } else {
      /* This character belong to an argument.  */
      if (!in_argument) {
        in_argument = 1;
      }
      if (!kwsysSystem__AppendByte(local_buffer, &buffer_begin, &buffer_end,
                                   &buffer_size, *c)) {
        failed = 1;
        break;
      }
    }