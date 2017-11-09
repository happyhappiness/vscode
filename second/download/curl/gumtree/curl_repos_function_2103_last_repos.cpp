void Curl_mime_initpart(curl_mimepart *part, struct Curl_easy *easy)
{
  memset((char *) part, 0, sizeof *part);
  part->easy = easy;
  mimesetstate(&part->state, MIMESTATE_BEGIN, NULL);
}