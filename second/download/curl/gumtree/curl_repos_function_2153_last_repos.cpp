bool Curl_recvpipe_head(struct Curl_easy *data,
                        struct connectdata *conn)
{
  return pipe_head(data, &conn->recv_pipe);
}