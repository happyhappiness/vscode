url = aprintf("%s://%s%s%s:%hu%s%s%s", conn->given->scheme,
                    conn->bits.ipv6_ip?"[":"", conn->host.name,
                    conn->bits.ipv6_ip?"]":"", conn->remote_port,
                    data->state.slash_removed?"/":"", data->state.path,
                    type);