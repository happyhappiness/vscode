#include "tool_cfgable.h"
#include "tool_msgs.h"
#include "tool_cb_wrt.h"

#include "memdebug.h" /* keep this as LAST include */

/*
** callback for CURLOPT_WRITEFUNCTION
*/

size_t tool_write_cb(void *buffer, size_t sz, size_t nmemb, void *userdata)
{
