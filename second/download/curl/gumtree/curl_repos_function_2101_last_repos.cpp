void curl_mime_free(curl_mime *mime)
{
  curl_mimepart *part;

  if(mime) {
    while(mime->firstpart) {
      part = mime->firstpart;
      mime->firstpart = part->nextpart;
      Curl_mime_cleanpart(part);
      free(part);
    }

    free(mime->boundary);
    free(mime);
  }
}