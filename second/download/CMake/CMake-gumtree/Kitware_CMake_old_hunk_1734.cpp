}



int

Curl_sec_vfprintf2(struct connectdata *conn, FILE *f, const char *fmt, va_list ap)

{

  char *buf;

  int ret;

  if(conn->data_prot == prot_clear)

    return vfprintf(f, fmt, ap);

  else {

    buf = aprintf(fmt, ap);

    ret = buffer_write(&conn->out_buffer, buf, strlen(buf));

    free(buf);

    return ret;

  }

}



int

Curl_sec_fprintf2(struct connectdata *conn, FILE *f, const char *fmt, ...)

{

    int ret;

    va_list ap;

    va_start(ap, fmt);

    ret = Curl_sec_vfprintf2(conn, f, fmt, ap);

    va_end(ap);

    return ret;

}



int

Curl_sec_putc(struct connectdata *conn, int c, FILE *F)

{

  char ch = c;

