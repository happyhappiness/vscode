bool Curl_sendpipe_head(struct Curl_easy *data,
                        struct connectdata *conn)
{
  return pipe_head(data, &conn->send_pipe);
}