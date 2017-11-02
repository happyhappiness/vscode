int check_metalink_content_type(const char *content_type)
{
  return check_content_type(content_type, "application/metalink+xml");
}