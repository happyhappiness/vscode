static int mime_part_rewind(curl_mimepart *part)
{
  int res = CURL_SEEKFUNC_OK;
  enum mimestate targetstate = MIMESTATE_BEGIN;

  if(part->flags & MIME_BODY_ONLY)
    targetstate = MIMESTATE_BODY;
  cleanup_encoder_state(&part->encstate);
  if(part->state.state > targetstate) {
    res = CURL_SEEKFUNC_CANTSEEK;
    if(part->seekfunc) {
      res = part->seekfunc(part->arg, (curl_off_t) 0, SEEK_SET);
      switch(res) {
      case CURL_SEEKFUNC_OK:
      case CURL_SEEKFUNC_FAIL:
      case CURL_SEEKFUNC_CANTSEEK:
        break;
      case -1:    /* For fseek() error. */
        res = CURL_SEEKFUNC_CANTSEEK;
        break;
      default:
        res = CURL_SEEKFUNC_FAIL;
        break;
      }
    }
  }

  if(res == CURL_SEEKFUNC_OK)
    mimesetstate(&part->state, targetstate, NULL);

  return res;
}