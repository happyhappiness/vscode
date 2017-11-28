 SQUIDCEXTERN int expiresMoreThan(time_t, time_t);
 
 /// \ingroup StoreAPI
 SQUIDCEXTERN void storeAppendPrintf(StoreEntry *, const char *,...) PRINTF_FORMAT_ARG2;
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeAppendVPrintf(StoreEntry *, const char *, va_list ap);
+extern void storeAppendVPrintf(StoreEntry *, const char *, va_list ap);
 
 /// \ingroup StoreAPI
 SQUIDCEXTERN int storeTooManyDiskFilesOpen(void);
 
 class SwapDir;
 /// \ingroup StoreAPI
