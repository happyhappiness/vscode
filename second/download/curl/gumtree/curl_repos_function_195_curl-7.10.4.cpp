int curl_formparse(char *input,
                   struct curl_httppost **httppost,
                   struct curl_httppost **last_post)
{
  return FormParse(input, httppost, last_post);
}