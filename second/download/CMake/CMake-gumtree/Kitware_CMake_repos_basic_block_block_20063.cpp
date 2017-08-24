(r == SOCKET_ERROR)
    return uv_translate_sys_error(WSAGetLastError());