
static void test_reply_reader() {
    void *reader;
    void *reply;
    char *err;
    int ret;

    test("Error handling in reply parser: ");
    reader = redisReplyReaderCreate();
    redisReplyReaderFeed(reader,(char*)"@foo\r\n",6);
    ret = redisReplyReaderGetReply(reader,NULL);
    err = redisReplyReaderGetError(reader);
