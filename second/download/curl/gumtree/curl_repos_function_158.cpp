static gboolean fifo_cb (GIOChannel *ch, GIOCondition condition, gpointer data)
{
  #define BUF_SIZE 1024
  gsize len, tp;
  gchar *buf, *tmp, *all=NULL;
  GIOStatus rv;

  do {
    GError *err=NULL;
    rv = g_io_channel_read_line (ch,&buf,&len,&tp,&err);
    if ( buf ) {
      if (tp) { buf[tp]='\0'; }
      new_conn(buf,(GlobalInfo*)data);
      g_free(buf);
    } else {
      buf = g_malloc(BUF_SIZE+1);
      while (TRUE) {
        buf[BUF_SIZE]='\0';
        g_io_channel_read_chars(ch,buf,BUF_SIZE,&len,&err);
        if (len) {
          buf[len]='\0';
          if (all) {
            tmp=all;
            all=g_strdup_printf("%s%s", tmp, buf);
            g_free(tmp);
          } else {
            all = g_strdup(buf);
          }
        } else {
           break;
        }
      }
      if (all) {
        new_conn(all,(GlobalInfo*)data);
        g_free(all);
      }
      g_free(buf);
    }
    if ( err ) {
      g_error("fifo_cb: %s", err->message);
      g_free(err);
      break;
    }
  } while ( (len) && (rv == G_IO_STATUS_NORMAL) );
  return TRUE;
}