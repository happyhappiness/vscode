int FormAddTest(const char * errormsg,
                 struct HttpPost **httppost,
                 struct HttpPost **last_post,
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