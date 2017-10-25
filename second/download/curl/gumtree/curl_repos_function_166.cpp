void telwrite(struct UrlData *data,
	      unsigned char *buffer,	/* Data to write */
	      int count)		/* Number of bytes to write */
{
   unsigned char outbuf[2];
   int out_count = 0;
   int bytes_written;

   while(count--)
   {
      outbuf[0] = *buffer++;
      out_count = 1;
      if(outbuf[0] == IAC)
	 outbuf[out_count++] = IAC;
      
#ifndef USE_SSLEAY
      bytes_written = swrite(data->firstsocket, outbuf, out_count);
#else
      if (data->use_ssl) {
        bytes_written = SSL_write(data->ssl, (char *)outbuf, out_count);
      }
      else {
        bytes_written = swrite(data->firstsocket, outbuf, out_count);
      }
#endif /* USE_SSLEAY */
   }
}