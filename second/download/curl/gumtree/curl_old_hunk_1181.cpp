

#endif

#include "urldata.h"
#include <curl/curl.h>
#include "download.h"
#include "sendf.h"
#include "formdata.h"
#include "progress.h"
#include "base64.h"
#include "cookie.h"
#include "strequal.h"
#include "url.h"
#include "ssluse.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

/* The last #include file should be: */
#ifdef MALLOCDEBUG
#include "memdebug.h"
#endif

/*
 * This function checks the linked list of custom HTTP headers for a particular
 * header (prefix).
 */
bool static checkheaders(struct UrlData *data, char *thisheader)
{
  struct curl_slist *head;
