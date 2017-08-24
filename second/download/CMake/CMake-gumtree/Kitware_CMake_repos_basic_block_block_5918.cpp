{
          infof(data, "Server doesn't support multi-use yet, wait\n");
          *waitpipe = TRUE;
          return FALSE; /* no re-use */
        }