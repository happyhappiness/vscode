{
        case AF_INET:
            return sizeof(struct sockaddr_in);
        case AF_INET6:
            return sizeof(struct sockaddr_in6);
        case AF_PACKET:
            return maxSize(sizeof(struct sockaddr_ll), offsetof(struct sockaddr_ll, sll_addr) + p_dataSize);
        default:
            return maxSize(sizeof(struct sockaddr), offsetof(struct sockaddr, sa_data) + p_dataSize);
    }