*/

/* Now setup curlx_ * names for the functions that are to become curlx_ and
   be removed from a future libcurl official API:
   curlx_getenv
   curlx_mprintf (and its variations)
   curlx_strequal
   curlx_strnequal

*/

#define curlx_getenv curl_getenv
#define curlx_strequal curl_strequal
#define curlx_strnequal curl_strnequal
#define curlx_raw_equal Curl_raw_equal
#define curlx_mvsnprintf curl_mvsnprintf
#define curlx_msnprintf curl_msnprintf
#define curlx_maprintf curl_maprintf
#define curlx_mvaprintf curl_mvaprintf
#define curlx_msprintf curl_msprintf
#define curlx_mprintf curl_mprintf
