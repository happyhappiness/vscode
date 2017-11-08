void Curl_ntlm_wb_cleanup(struct connectdata *conn)
{
  if(conn->ntlm_auth_hlpr_socket != CURL_SOCKET_BAD) {
    sclose(conn->ntlm_auth_hlpr_socket);
    conn->ntlm_auth_hlpr_socket = CURL_SOCKET_BAD;
  }

  if(conn->ntlm_auth_hlpr_pid) {
    int i;
    for(i = 0; i < 4; i++) {
      pid_t ret = waitpid(conn->ntlm_auth_hlpr_pid, NULL, WNOHANG);
      if(ret == conn->ntlm_auth_hlpr_pid || errno == ECHILD)
        break;
      switch(i) {
      case 0:
        kill(conn->ntlm_auth_hlpr_pid, SIGTERM);
        break;
      case 1:
        /* Give the process another moment to shut down cleanly before
           bringing down the axe */
        Curl_wait_ms(1);
        break;
      case 2:
        kill(conn->ntlm_auth_hlpr_pid, SIGKILL);
        break;
      case 3:
        break;
      }
    }
    conn->ntlm_auth_hlpr_pid = 0;
  }

  Curl_safefree(conn->challenge_header);
  conn->challenge_header = NULL;
  Curl_safefree(conn->response_header);
  conn->response_header = NULL;
}