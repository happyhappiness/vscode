            addReply(c,shared.ok);
        }
    }

    sdsfree(cmd.io.buffer.ptr);
    close(fd);
    return;

