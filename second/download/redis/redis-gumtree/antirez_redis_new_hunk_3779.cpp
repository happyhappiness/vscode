        vmpointer *vp;

        if (!server.vm_enabled) {
            addReplyError(c,"Virtual Memory is disabled");
            return;
        }
        if (!de) {
