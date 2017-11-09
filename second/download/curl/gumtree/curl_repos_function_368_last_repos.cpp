static int
Curl_is_formadd_string(CURLformoption option)

{
  switch (option) {

  case CURLFORM_FILENAME:
  case CURLFORM_CONTENTTYPE:
  case CURLFORM_BUFFER:
  case CURLFORM_FILE:
  case CURLFORM_FILECONTENT:
  case CURLFORM_COPYCONTENTS:
  case CURLFORM_COPYNAME:
    return 1;
  }

  return 0;
}