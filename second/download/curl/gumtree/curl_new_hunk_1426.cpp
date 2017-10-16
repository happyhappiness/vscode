            /* a newline is CRLF in ftp-talk, so the CR is ignored as
               the line isn't really terminated until the LF comes */

            /* output debug output if that is requested */
            if(data->bits.verbose) {
              fputs("< ", data->err);
              fwrite(line_start, perline, 1, data->err);
              /* no need to output LF here, it is part of the data */
            }

            if(perline>3 && lastline(line_start)) {
              /* This is the end of the last line, copy the last
               * line to the start of the buffer and zero terminate,
               * for old times sake (and krb4)! */
              char *meow;
              int i;
              for(meow=line_start, i=0; meow<ptr; meow++, i++)
                buf[i] = *meow;
              meow[i]=0; /* zero terminate */
              keepon=FALSE;
              break;
            }
            perline=0; /* line starts over here */
            line_start = ptr+1;
          }
