    return;

numargserr:
    addReplyErrorFormat(c,"Wrong number of commands for 'sentinel %s'",
                          (char*)c->argv[1]->ptr);
}

