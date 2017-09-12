static int cliReadReply(int fd) {
    char type;

    if (anetRead(fd,&type,1) <= 0) exit(1);
    switch(type) {
    case '-':
        printf("(error) ");
