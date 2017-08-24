f((pid_t)l_hdr->nlmsg_pid != l_pid || (int)l_hdr->nlmsg_seq != p_socket)
            {
                continue;
            }