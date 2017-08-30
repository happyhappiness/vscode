  va_start(ap_save, format);

  retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);

  va_end(ap_save);

  if(-1 == retcode) {

    if(info.alloc)

      free(info.buffer);

    return NULL;

  }

  if(info.alloc) {

    info.buffer[info.len] = 0; /* we terminate this with a zero byte */

    return info.buffer;

  }

  else

    return strdup("");

}



char *curl_mvaprintf(const char *format, va_list ap_save)

