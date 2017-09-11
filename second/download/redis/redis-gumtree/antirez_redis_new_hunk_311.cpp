    if (pos >= 15 && pos <= 19) tag = "new accessed ";
    if (pos >= keyspace_size -5) tag= "old no access";

    printf("%ld] <%s> frequency:%d decrtime:%d [%lu hits | age:%ld sec]\n",
        pos, tag, e->counter, e->decrtime, (unsigned long)e->hits,
            time(NULL) - e->ctime);
}
