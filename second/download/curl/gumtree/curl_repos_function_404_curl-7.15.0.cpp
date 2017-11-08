int FormAddTest(const char * errormsg,
                 struct curl_httppost **httppost,
                 struct curl_httppost **last_post,
                 ...)
{
  int result;
  va_list arg;
  va_start(arg, last_post);
  if ((result = FormAdd(httppost, last_post, arg)))
    fprintf (stderr, "ERROR doing FormAdd ret: %d action: %s\n", result,
             errormsg);
  va_end(arg);
  return result;
}