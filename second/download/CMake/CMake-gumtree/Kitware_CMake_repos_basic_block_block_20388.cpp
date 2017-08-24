{
        QUEUE* q;
        SOCKET socket;

        q = QUEUE_HEAD(&handle->pipe.conn.pending_ipc_info.queue);
        QUEUE_REMOVE(q);
        item = QUEUE_DATA(q, uv__ipc_queue_item_t, member);

        /* Materialize socket and close it */
        socket = WSASocketW(FROM_PROTOCOL_INFO,
                            FROM_PROTOCOL_INFO,
                            FROM_PROTOCOL_INFO,
                            &item->socket_info_ex.socket_info,
                            0,
                            WSA_FLAG_OVERLAPPED);
        uv__free(item);

        if (socket != INVALID_SOCKET)
          closesocket(socket);
      }