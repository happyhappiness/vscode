void *dupClientReplyValue(void *o);
void getClientsMaxBuffers(unsigned long *longest_output_list,
                          unsigned long *biggest_input_buffer);

#ifdef __GNUC__
void addReplyErrorFormat(redisClient *c, const char *fmt, ...)
