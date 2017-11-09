CURLcode Curl_mime_rewind(curl_mimepart *part)
{
  return mime_part_rewind(part) == CURL_SEEKFUNC_OK?
         CURLE_OK: CURLE_SEND_FAIL_REWIND;
}