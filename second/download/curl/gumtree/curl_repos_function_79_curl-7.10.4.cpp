int my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct OutStruct *out=(struct OutStruct *)stream;
  struct Configurable *config = out->config;
  if(out && !out->stream) {
    /* open file for writing */
    out->stream=fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure */
    if(config->nobuffer) {
      /* disable output buffering */
#ifdef HAVE_SETVBUF
      setvbuf(out->stream, NULL, _IONBF, 0);
#endif
    }
  }

  if(config->recvpersecond) {
    /*
     * We know when we received data the previous time. We know how much data
     * we get now. Make sure that this is not faster than we are told to run.
     * If we're faster, sleep a while *before* doing the fwrite() here.
     */

    time_t timediff;
    time_t now;

    now = time(NULL);
    timediff = now - config->lastrecvtime;
    if( size*nmemb > config->recvpersecond*timediff) {
      /* figure out how many milliseconds to rest */
      go_sleep ( (size*nmemb)*1000/config->recvpersecond - timediff*1000 );
      now = time(NULL);
    }
    config->lastrecvtime = now;
  }

  return fwrite(buffer, size, nmemb, out->stream);
}