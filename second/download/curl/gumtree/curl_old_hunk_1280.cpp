              ++ptr;
            *ptr2++ = *ptr++;
          }
          while(ptr < *end_pos);
          *end_pos = ptr2;
        }
        while(*ptr && NULL==strchr(end_chars, *ptr))
          ++ptr;
        *str = ptr;
        return word_begin+1;
      }
      ++ptr;
    }
    /* end quote is missing, treat it as non-quoted. */
    ptr = word_begin;
  }

  while(*ptr && NULL==strchr(end_chars, *ptr))
    ++ptr;
  *str = *end_pos = ptr;
  return word_begin;
}

/***************************************************************************
 *
 * formparse()
 *
 * Reads a 'name=value' parameter and builds the appropriate linked list.
 *
