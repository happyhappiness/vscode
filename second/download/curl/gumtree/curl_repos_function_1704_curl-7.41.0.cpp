static bool ftp_pl_gettime(struct ftp_parselist_data *parser, char *string)
{
  (void)parser;
  (void)string;
  /* TODO
   * There could be possible parse timestamp from server. Leaving unimplemented
   * for now.
   * If you want implement this, please add CURLFINFOFLAG_KNOWN_TIME flag to
   * parser->file_data->flags
   *
   * Ftp servers are giving usually these formats:
   *  Apr 11  1998 (unknown time.. set it to 00:00:00?)
   *  Apr 11 12:21 (unknown year -> set it to NOW() time?)
   *  08-05-09  02:49PM  (ms-dos format)
   *  20100421092538 -> for MLST/MLSD response
   */

  return FALSE;
}