            char *errmsg = "operation not possible.";
            switch(errno) {
            case ENOENT: errmsg = "no such module with that name";
            case EBUSY: errmsg = "the module exports one or more module-side data types, can't unload";
            }
            addReplyErrorFormat(c,"Error unloading module: %s",errmsg);
        }
