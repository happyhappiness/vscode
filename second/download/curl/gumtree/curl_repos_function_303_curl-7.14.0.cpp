static char *max5data(curl_off_t bytes, char *max5)
{
#define ONE_KILOBYTE 1024
#define ONE_MEGABYTE (1024* ONE_KILOBYTE)
#define ONE_GIGABYTE (1024* ONE_MEGABYTE)
#define ONE_TERRABYTE ((curl_off_t)1024* ONE_GIGABYTE)
#define ONE_PETABYTE ((curl_off_t)1024* ONE_TERRABYTE)

  if(bytes < 100000) {
    snprintf(max5, 6, "%5" FORMAT_OFF_T, bytes);
  }
  else if(bytes < (10000*ONE_KILOBYTE)) {
    snprintf(max5, 6, "%4" FORMAT_OFF_T "k", (curl_off_t)(bytes/ONE_KILOBYTE));
  }
  else if(bytes < (100*ONE_MEGABYTE)) {
    /* 'XX.XM' is good as long as we're less than 100 megs */
    snprintf(max5, 6, "%2d.%0dM",
             (int)(bytes/ONE_MEGABYTE),
             (int)(bytes%ONE_MEGABYTE)/(ONE_MEGABYTE/10) );
  }
#if SIZEOF_CURL_OFF_T > 4
  else if(bytes < ( (curl_off_t)10000*ONE_MEGABYTE))
    /* 'XXXXM' is good until we're at 10000MB or above */
    snprintf(max5, 6, "%4" FORMAT_OFF_T "M", (curl_off_t)(bytes/ONE_MEGABYTE));

  else if(bytes < (curl_off_t)100*ONE_GIGABYTE)
    /* 10000 MB - 100 GB, we show it as XX.XG */
    snprintf(max5, 6, "%2d.%0dG",
             (int)(bytes/ONE_GIGABYTE),
             (int)(bytes%ONE_GIGABYTE)/(ONE_GIGABYTE/10) );

  else if(bytes < (curl_off_t)10000 * ONE_GIGABYTE)
    /* up to 10000GB, display without decimal: XXXXG */
    snprintf(max5, 6, "%4dG", (int)(bytes/ONE_GIGABYTE));

  else if(bytes < (curl_off_t)10000 * ONE_TERRABYTE)
    /* up to 10000TB, display without decimal: XXXXT */
    snprintf(max5, 6, "%4dT", (int)(bytes/ONE_TERRABYTE));
  else {
    /* up to 10000PB, display without decimal: XXXXP */
    snprintf(max5, 6, "%4dP", (int)(bytes/ONE_PETABYTE));

    /* 16384 petabytes (16 exabytes) is maximum a 64 bit number can hold,
       but this type is signed so 8192PB will be max.*/
  }

#else
  else
    snprintf(max5, 6, "%4" FORMAT_OFF_T "M", (curl_off_t)(bytes/ONE_MEGABYTE));
#endif

  return max5;
}