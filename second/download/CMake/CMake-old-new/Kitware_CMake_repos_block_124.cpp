{
          /* for each digit in the integer part, we can have one less
             precision */
          size_t maxprec = sizeof(work) - 2;
          double val = p->data.dnum;
          while(val >= 10.0) {
            val /= 10;
            maxprec--;
          }

          if(prec > (long)maxprec)
            prec = (long)maxprec-1;
          /* RECURSIVE USAGE */
          len = curl_msnprintf(fptr, left, ".%ld", prec);
          fptr += len;
        }