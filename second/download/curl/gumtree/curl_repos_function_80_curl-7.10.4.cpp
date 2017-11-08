int my_fread(void *buffer, size_t size, size_t nmemb, void *userp)
{
  struct InStruct *in=(struct InStruct *)userp;

  struct Configurable *config = in->config;

  if(config->sendpersecond) {
    /*
     * We know when we sent data the previous time. We know how much data
     * we sent. Make sure that this was not faster than we are told to run.
     * If we're faster, sleep a while *before* doing the fread() here.
     * Also, make no larger fread() than should be sent this second!
     */

    time_t timediff;
    time_t now;

    now = time(NULL);
    timediff = now - config->lastsendtime;
    if( config->lastsendsize > config->sendpersecond*timediff) {
      /* figure out how many milliseconds to rest */
      go_sleep ( config->lastsendsize*1000/config->sendpersecond -
                 timediff*1000 );
      now = time(NULL);
    }
    config->lastsendtime = now;

    if(size*nmemb > config->sendpersecond) {
      /* lower the size to actually read */
      nmemb = config->sendpersecond;
      size = 1;
    }
    config->lastsendsize = size*nmemb;    
  }


  return fread(buffer, size, nmemb, in->stream);
}