/* use our own printf() functions */
#include "curlx.h"

#include "tool_cfgable.h"
#include "tool_convert.h"
#include "tool_operhlp.h"
#include "tool_metalink.h"

#include "memdebug.h" /* keep this as LAST include */

void clean_getout(struct OperationConfig *config)
{
  struct getout *next;
  struct getout *node = config->url_list;

  while(node) {
    next = node->next;
