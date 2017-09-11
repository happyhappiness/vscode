    funcdef = sdscatlen(funcdef,funcname,42);
    funcdef = sdscatlen(funcdef,"() ",3);
    funcdef = sdscatlen(funcdef,body->ptr,sdslen(body->ptr));
    funcdef = sdscatlen(funcdef," end",4);

    if (luaL_loadbuffer(lua,funcdef,sdslen(funcdef),"@user_script")) {
        addReplyErrorFormat(c,"Error compiling script (new function): %s\n",
