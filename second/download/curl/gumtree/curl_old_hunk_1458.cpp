        nread += gotbytes;
        for(i = 0; i < gotbytes; ptr++, i++) {
          perline++;
          if(*ptr=='\n') {
            /* a newline is CRLF in ftp-talk, so the CR is ignored as
               the line isn't really terminated until the LF comes */

            /* output debug output if that is requested */
            if(data->set.verbose) {
              fputs("< ", data->set.err);
              fwrite(line_start, perline, 1, data->set.err);
              /* no need to output LF here, it is part of the data */
            }

#define lastline(line) (isdigit((int)line[0]) && isdigit((int)line[1]) && \
			isdigit((int)line[2]) && (' ' == line[3]))

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
        }
      }
      break;
    } /* switch */
  } /* while there's buffer left and loop is requested */

  if(!error)
    code = atoi(buf);

#if KRB4
  /* handle the security-oriented responses 6xx ***/
  /* FIXME: some errorchecking perhaps... ***/
  switch(code) {
  case 631:
    Curl_sec_read_msg(conn, buf, prot_safe);
    break;
