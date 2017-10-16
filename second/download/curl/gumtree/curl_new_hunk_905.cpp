#include "tool_cfgable.h"
#include "tool_msgs.h"
#include "tool_cb_wrt.h"

#include "memdebug.h" /* keep this as LAST include */

/* create a local file for writing, return TRUE on success */
bool tool_create_output_file(struct OutStruct *outs)
{
  struct GlobalConfig *global = outs->config->global;
  FILE *file;

  if(!outs->filename || !*outs->filename) {
    warnf(global, "Remote filename has no length!\n");
    return FALSE;
  }

  if(outs->is_cd_filename) {
    /* don't overwrite existing files */
    file = fopen(outs->filename, "rb");
    if(file) {
      fclose(file);
      warnf(global, "Refusing to overwrite %s: %s\n", outs->filename,
            strerror(EEXIST));
      return FALSE;
    }
  }

  /* open file for writing */
  file = fopen(outs->filename, "wb");
  if(!file) {
    warnf(global, "Failed to create the file %s: %s\n", outs->filename,
          strerror(errno));
    return FALSE;
  }
  outs->s_isreg = TRUE;
  outs->fopened = TRUE;
  outs->stream = file;
  outs->bytes = 0;
  outs->init = 0;
  return TRUE;
}

/*
** callback for CURLOPT_WRITEFUNCTION
*/

size_t tool_write_cb(void *buffer, size_t sz, size_t nmemb, void *userdata)
{
