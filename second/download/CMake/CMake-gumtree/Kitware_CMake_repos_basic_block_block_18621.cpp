f(bind(l_socket, (struct sockaddr *)&l_addr, sizeof(l_addr)) < 0)
    {
        close(l_socket);
        return -1;
    }