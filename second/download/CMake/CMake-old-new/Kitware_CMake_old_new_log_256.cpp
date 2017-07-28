aprintf("%s:%d:%d:%s:%hu", data->set.str[STRING_SSL_CAFILE],
                data->set.ssl.verifypeer, data->set.ssl.verifyhost,
                conn->host.name, conn->remote_port)