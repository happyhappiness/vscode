                    break;
                }
            }
            if (!bound) {
                anetSetError(err, "bind: %s", strerror(errno));
                goto end;
