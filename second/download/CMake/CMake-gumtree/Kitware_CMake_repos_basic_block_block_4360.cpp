f(line_start[1] == '\n') {
                /* this can only be a LF if the letter at index 0
                   was a CR */
                line_start++;
              }