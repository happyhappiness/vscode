void Curl_expire_done(struct Curl_easy *data, expire_id id)
{
  /* remove the timer, if there */
  multi_deltimeout(data, id);
}