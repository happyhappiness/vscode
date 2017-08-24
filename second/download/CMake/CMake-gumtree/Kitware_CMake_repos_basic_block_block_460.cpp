(num == 4)
        {
          bp += len;            /* Make bp point to what sscanf() left */
          while (*bp && isspace((int)(*bp)))
            bp++;               /* Allow trailing whitespace */
        }