# undef vsnprintf
# undef aprintf
# undef vaprintf
# define printf curl_mprintf
# define fprintf curl_mfprintf
#ifdef CURLDEBUG
/* When built with CURLDEBUG we define away the sprintf() functions since we
   don't want internal code to be using them */
# define sprintf sprintf_was_used
# define vsprintf vsprintf_was_used
#else
# define sprintf curl_msprintf
# define vsprintf curl_mvsprintf
