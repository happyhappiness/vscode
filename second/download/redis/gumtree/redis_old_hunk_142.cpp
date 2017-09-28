        /* Handle the writable state: we can send protocol to the server. */
        if (mask & AE_WRITABLE) {
            while(1) {
                /* Transfer current buffer to server. */
                if (obuf_len != 0) {
                    ssize_t nwritten = write(fd,obuf+obuf_pos,obuf_len);
                    
                    if (nwritten == -1) {
                        if (errno != EAGAIN && errno != EINTR) {
                            fprintf(stderr, "Error writing to the server: %s\n",
                                strerror(errno));
                            exit(1);
                        } else {
