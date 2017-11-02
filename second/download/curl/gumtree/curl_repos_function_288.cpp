int
Curl_gsk_environment_init(gsk_handle my_env_handle)

{
  struct Curl_gsk_descriptor * p;

  if(!my_env_handle)
    return GSK_INVALID_HANDLE;
  p = (struct Curl_gsk_descriptor *) my_env_handle;
  return gsk_environment_init(p->h);
}