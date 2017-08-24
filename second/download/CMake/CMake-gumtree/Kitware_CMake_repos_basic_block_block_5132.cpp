{
          /* We got an excessive line without newlines and we need to deal
             with it. We keep the first bytes of the line then we throw
             away the rest. */
          infof(data, "Excessive server response line length received, "
                "%zd bytes. Stripping\n", gotbytes);
          restart = TRUE;

          /* we keep 40 bytes since all our pingpong protocols are only
             interested in the first piece */
          clipamount = 40;
        }