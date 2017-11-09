static void mime_subparts_free(void *ptr)
{
  curl_mime *mime = (curl_mime *) ptr;
  curl_mime_free(mime);
}