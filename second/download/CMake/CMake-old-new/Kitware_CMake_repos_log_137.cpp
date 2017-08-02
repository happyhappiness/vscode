snprintf(ptr, sizeof(hosturl)-(ptr-hosturl), "://%s:%d",
    conn->host.name, conn->remote_port)