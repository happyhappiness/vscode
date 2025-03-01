void read_sbuf(int f,char *buf,size_t len);
unsigned char read_byte(int f);
void io_start_buffering(int fd);
void io_flush(void);
void io_end_buffering(void);
void write_int(int f,int32 x);
void write_longint(int f, int64 x);
void write_buf(int f,char *buf,size_t len);
void write_byte(int f,unsigned char c);
int read_line(int f, char *buf, size_t maxlen);
void io_printf(int fd, const char *format, ...);
void io_start_multiplex_out(int fd);
