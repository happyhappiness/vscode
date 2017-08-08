{
          if(width >= (long)sizeof(work))
            width = sizeof(work)-1;
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, "%ld", width);
          fptr += len;
          left -= len;
        }