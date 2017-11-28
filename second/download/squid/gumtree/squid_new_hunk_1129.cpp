    LOGCLOSE *f_close;
};

/* Legacy API */
Logfile *logfileOpen(const char *path, size_t bufsz, int);
void logfileClose(Logfile * lf);
void logfileRotate(Logfile * lf, int16_t rotateCount);
void logfileWrite(Logfile * lf, char *buf, size_t len);
void logfileFlush(Logfile * lf);
void logfilePrintf(Logfile * lf, const char *fmt,...) PRINTF_FORMAT_ARG2;
void logfileLineStart(Logfile * lf);
void logfileLineEnd(Logfile * lf);

