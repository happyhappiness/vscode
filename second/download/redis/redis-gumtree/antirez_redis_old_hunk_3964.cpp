
    if (listTypeLength(subject) == 0) dbDelete(c->db,c->argv[1]);
    addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",removed));
}

/* This is the semantic of this command:
