        funcdef = sdscatlen(funcdef," ()\n",4);
        funcdef = sdscatlen(funcdef,c->argv[1]->ptr,sdslen(c->argv[1]->ptr));
        funcdef = sdscatlen(funcdef,"\nend\n",5);
        printf("Defining:\n%s\n",funcdef);

        if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"func definition")) {
            addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
