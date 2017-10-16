        nread++;
        ptr++;
      }
    }
    *ptr=0; /* zero terminate */

    if(data->bits.verbose && buf[0]) {
      fputs("< ", data->err);
      fwrite(buf, 1, nread, data->err);
      fputs("\n", data->err);
    }
  } while(!error &&
