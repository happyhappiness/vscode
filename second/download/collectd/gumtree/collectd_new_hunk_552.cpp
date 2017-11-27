        }
        else if (dot) { /* floating point value */
          values[values_len].gauge = strtod (value, &endptr);
          values_types[values_len] = LCC_TYPE_GAUGE;
        }
        else { /* integer */
          values[values_len].counter = (counter_t) strtoull (value, &endptr, 0);
          values_types[values_len] = LCC_TYPE_COUNTER;
        }
        ++values_len;

        if (endptr == value) {
          fprintf (stderr, "ERROR: Failed to parse value as number: %s.\n",
