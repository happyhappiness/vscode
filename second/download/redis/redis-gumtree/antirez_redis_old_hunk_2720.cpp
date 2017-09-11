            enableWatchdog(ll);
        else
            disableWatchdog();
    } else {
        addReplyErrorFormat(c,"Unsupported CONFIG parameter: %s",
            (char*)c->argv[2]->ptr);
