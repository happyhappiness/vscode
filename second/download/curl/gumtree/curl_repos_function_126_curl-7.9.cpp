int curl_formadd(struct HttpPost **httppost,
                 struct HttpPost **last_post,
                 ...)
{
  va_list arg;
  int result;
  va_start(arg, last_post);
  result = FormAdd(httppost, last_post, arg);
  va_end(arg);
  return result;
}