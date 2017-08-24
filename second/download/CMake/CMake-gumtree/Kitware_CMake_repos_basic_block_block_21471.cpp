(gethostname(buf, sizeof(buf)) != 0)
    return uv_translate_sys_error(WSAGetLastError());