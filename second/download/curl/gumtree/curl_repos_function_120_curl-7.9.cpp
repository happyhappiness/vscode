int curl_formparse(char *input,
                   struct HttpPost **httppost,
                   struct HttpPost **last_post)
{
  return FormParse(input, httppost, last_post);
}