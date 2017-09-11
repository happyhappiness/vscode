    return;

numargserr:
    addReplyErrorFormat(c,"Wrong number of arguments for 'sentinel %s'",
                          (char*)c->argv[1]->ptr);
}

