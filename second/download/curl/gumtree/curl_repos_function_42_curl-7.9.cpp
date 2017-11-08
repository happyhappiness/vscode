int my_fwrite(void *buffer, size_t size, size_t nmemb, void *stream)
{
  struct OutStruct *out=(struct OutStruct *)stream;
  if(out && !out->stream) {
    /* open file for writing */
    out->stream=fopen(out->filename, "wb");
    if(!out->stream)
      return -1; /* failure */
    if(out->config->nobuffer) {
      /* disable output buffering */
#ifdef HAVE_SETVBUF
      setvbuf(out->stream, NULL, _IONBF, 0);
#endif
    }
  }
  return fwrite(buffer, size, nmemb, out->stream);
}