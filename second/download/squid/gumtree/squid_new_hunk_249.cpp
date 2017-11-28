
        if (recvfrom(0, buf, RECV_BUF_SIZE, 0, (sockaddr *)&R, &len) < 0) {
            perror("recv");
            exit(2);
        }

        memcpy(ip, &R.sin_addr.s_addr, 4);
        hp = gethostbyaddr(ip, 4, AF_INET);
        ipa = R.sin_addr;
        printf("==============================================================================\n");
        printf("Received from %s [%s]\n",
               ipa.NtoA(tmp,MAX_HOSTNAMELEN),
               (hp && hp->h_name) ? hp->h_name : "Unknown");
