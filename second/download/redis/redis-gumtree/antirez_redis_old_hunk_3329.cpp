            addReplyErrorFormat(c,"Changing directory: %s", strerror(errno));
            return;
        }
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
