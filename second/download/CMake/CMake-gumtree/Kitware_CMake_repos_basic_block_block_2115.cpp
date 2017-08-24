{
            // Assume the argument contributes no more than 64 characters.
            length += 64;

            // Eat the argument.
            static_cast<void>(va_arg(ap, double));
          }