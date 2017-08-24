{
            pid_t l_pid = getpid();
            struct nlmsghdr *l_hdr;
            for(l_hdr = (struct nlmsghdr *)l_buffer; NLMSG_OK(l_hdr, (unsigned int)l_read); l_hdr = (struct nlmsghdr *)NLMSG_NEXT(l_hdr, l_read))
            {
                if((pid_t)l_hdr->nlmsg_pid != l_pid || (int)l_hdr->nlmsg_seq != p_socket)
                {
                    continue;
                }

                if(l_hdr->nlmsg_type == NLMSG_DONE)
                {
                    *p_done = 1;
                    break;
                }

                if(l_hdr->nlmsg_type == NLMSG_ERROR)
                {
                    uv__free(l_buffer);
                    return NULL;
                }
            }
            return l_buffer;
        }