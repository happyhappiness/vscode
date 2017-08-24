f(drc) {
            /* a failure here pretty much implies an out of memory */
            result = drc;
            stream_error = TRUE;
          }
          else
            retry = (newurl)?TRUE:FALSE