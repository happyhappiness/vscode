static void randomizeClientKey(client c) {
    char *p;
    char buf[32];
    long r;

    p = strstr(c->obuf, "_rand");
    if (!p) return;
    p += 5;
    r = random() % config.randomkeys_keyspacelen;
    sprintf(buf,"%ld",r);
    memcpy(p,buf,strlen(buf));
}