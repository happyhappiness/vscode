(*cur++ == '%') {
      // Skip "%%" since it doesn't correspond to a va_arg.
      if (*cur != '%') {
        while (!int(isalpha(*cur))) {
          ++cur;
        }
        switch (*cur) {
          case 's': {
            // Check the length of the string.
            char* s = va_arg(ap, char*);
            if (s) {
              length += strlen(s);
            }
          } break;
          case 'e':
          case 'f':
          case 'g': {
            // Assume the argument contributes no more than 64 characters.
            length += 64;

            // Eat the argument.
            static_cast<void>(va_arg(ap, double));
          } break;
          default: {
            // Assume the argument contributes no more than 64 characters.
            length += 64;

            // Eat the argument.
            static_cast<void>(va_arg(ap, int));
          } break;
        }
      }

      // Move past the characters just tested.
      ++cur;
    }