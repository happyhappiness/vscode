{
    infof(data, "NTLM handshake failure (type-3 message): Status=%x\n",
          status);

    return CURLE_RECV_ERROR;
  }