 *

 * If you ever want truly portable and good *printf() clones, the project that

 * took on from here is named 'Trio' and you find more details on the trio web

 * page at http://daniel.haxx.se/trio/

 */



#include "curl_setup.h"



#if defined(DJGPP) && (DJGPP_MINOR < 4)

#undef _MPRINTF_REPLACE /* don't use x_was_used() here */

#endif



#include <curl/mprintf.h>



#include "curl_memory.h"

