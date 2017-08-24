{
    peer_socket = uv__fast_poll_create_peer_socket(loop->iocp, protocol_info);
    loop->poll_peer_sockets[index] = peer_socket;
  }