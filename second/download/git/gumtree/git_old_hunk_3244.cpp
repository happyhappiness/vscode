
int start_async(struct async *async);
int finish_async(struct async *async);
int in_async(void);
void NORETURN async_exit(int code);

#endif
