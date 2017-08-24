{
  case CURLE_ABORTED_BY_CALLBACK:
  case CURLE_READ_ERROR:
  case CURLE_WRITE_ERROR:
    /* When we're aborted due to a callback return code it basically have to
       be counted as premature as there is trouble ahead if we don't. We have
       many callbacks and protocols work differently, we could potentially do
       this more fine-grained in the future. */
    premature = TRUE;
  default:
    break;
  }