{
          /* This argument has been terminated by whitespace.  */
          if (!kwsysSystem__AppendArgument(
                local_pointers, &pointer_begin, &pointer_end, &pointers_size,
                local_buffer, &buffer_begin, &buffer_end, &buffer_size)) {
            failed = 1;
            break;
          }
          in_argument = 0;
        }