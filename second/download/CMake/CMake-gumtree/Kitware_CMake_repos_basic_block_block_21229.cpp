{
            /* Multibyte sequence */
            utf8_codepoint = (0xff >> (8 - first_zero_bit)) & c;
            utf8_bytes_left = (char) (6 - first_zero_bit);

          }