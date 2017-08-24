(first_zero_bit == 7) {
            /* Ascii - pass right through */
            utf8_codepoint = (unsigned int) c;

          } else if (first_zero_bit <= 5) {
            /* Multibyte sequence */
            utf8_codepoint = (0xff >> (8 - first_zero_bit)) & c;
            utf8_bytes_left = (char) (6 - first_zero_bit);

          } else {
            /* Invalid continuation */
            utf8_codepoint = UNICODE_REPLACEMENT_CHARACTER;
          }