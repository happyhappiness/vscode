            char *errmsg = "operation not possible.";
            switch(errno) {
            case ENOENT: errmsg = "no such module with that name";
            }
            addReplyErrorFormat(c,"Error unloading module: %s",errmsg);
        }
