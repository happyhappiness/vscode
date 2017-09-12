
    for (i = 0; i < c->randlen; i++) {
        r = random() % config.randomkeys_keyspacelen;
        snprintf(buf,sizeof(buf),"%012lu",r);
        memcpy(c->randptr[i],buf,12);
    }
}
