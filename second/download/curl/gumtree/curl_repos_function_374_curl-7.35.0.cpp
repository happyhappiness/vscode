static int checkForCompletion(CURLM* curl, int* success)
{
  int numMessages;
  CURLMsg* message;
  int result = 0;
  *success = 0;
  while ((message = curl_multi_info_read(curl, &numMessages)) != NULL) {
    if (message->msg == CURLMSG_DONE) {
      result = 1;
      if (message->data.result == CURLE_OK)
        *success = 1;
      else
        *success = 0;
    }
    else {
      fprintf(stderr, "Got an unexpected message from curl: %i\n",
              (int)message->msg);
      result = 1;
      *success = 0;
    }
  }
  return result;
}