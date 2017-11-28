/* some uint8_t do not like streaming control-chars (values 0-31, 127+) */
inline std::ostream& operator <<(std::ostream &os, const uint8_t d)
{
    return (os << (int)d);
}

/* Legacy debug function definitions */
void _db_init(const char *logfile, const char *options);
void _db_print(const char *,...) PRINTF_FORMAT_ARG1;
void _db_set_syslog(const char *facility);
void _db_rotate_log(void);

