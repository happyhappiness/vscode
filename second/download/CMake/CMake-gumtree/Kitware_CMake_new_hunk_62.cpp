    info.buffer[info.len] = 0; /* we terminate this with a zero byte */
    return info.buffer;
  }
  return strdup("");
}

char *curl_mvaprintf(const char *format, va_list ap_save)
