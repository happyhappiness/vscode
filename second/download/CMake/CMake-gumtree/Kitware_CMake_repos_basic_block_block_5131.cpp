{
          /* We got a large chunk of data and there's potentially still
             trailing data to take care of, so we put any such part in the
             "cache", clear the buffer to make space and restart. */
          clipamount = perline;
          restart = TRUE;
        }