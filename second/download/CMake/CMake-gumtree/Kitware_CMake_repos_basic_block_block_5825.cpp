{
    signalPipeClose(&conn->send_pipe, TRUE);
    signalPipeClose(&conn->recv_pipe, TRUE);
  }