snprintf((char *)state->spacket.data+2,
             state->blksize,
             "%s%c%s%c", filename, '\0',  mode, '\0');