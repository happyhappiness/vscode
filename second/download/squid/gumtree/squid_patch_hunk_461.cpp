 };
 
 /// \ingroup StoreAPI
 typedef RefCount<Store> StorePointer;
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN size_t storeEntryInUse();
+size_t storeEntryInUse();
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN const char *storeEntryFlags(const StoreEntry *);
+const char *storeEntryFlags(const StoreEntry *);
 
 /// \ingroup StoreAPI
-extern void storeEntryReplaceObject(StoreEntry *, HttpReply *);
+void storeEntryReplaceObject(StoreEntry *, HttpReply *);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN StoreEntry *storeGetPublic(const char *uri, const HttpRequestMethod& method);
+StoreEntry *storeGetPublic(const char *uri, const HttpRequestMethod& method);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN StoreEntry *storeGetPublicByRequest(HttpRequest * request);
+StoreEntry *storeGetPublicByRequest(HttpRequest * request);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN StoreEntry *storeGetPublicByRequestMethod(HttpRequest * request, const HttpRequestMethod& method);
+StoreEntry *storeGetPublicByRequestMethod(HttpRequest * request, const HttpRequestMethod& method);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN StoreEntry *storeCreateEntry(const char *, const char *, request_flags, const HttpRequestMethod&);
+StoreEntry *storeCreateEntry(const char *, const char *, const RequestFlags &, const HttpRequestMethod&);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeInit(void);
+void storeInit(void);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeConfigure(void);
+void storeConfigure(void);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeFreeMemory(void);
+void storeFreeMemory(void);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN int expiresMoreThan(time_t, time_t);
+int expiresMoreThan(time_t, time_t);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeAppendPrintf(StoreEntry *, const char *,...) PRINTF_FORMAT_ARG2;
+void storeAppendPrintf(StoreEntry *, const char *,...) PRINTF_FORMAT_ARG2;
 
 /// \ingroup StoreAPI
-extern void storeAppendVPrintf(StoreEntry *, const char *, va_list ap);
+void storeAppendVPrintf(StoreEntry *, const char *, va_list ap);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN int storeTooManyDiskFilesOpen(void);
+int storeTooManyDiskFilesOpen(void);
 
 class SwapDir;
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeHeapPositionUpdate(StoreEntry *, SwapDir *);
+void storeHeapPositionUpdate(StoreEntry *, SwapDir *);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeSwapFileNumberSet(StoreEntry * e, sfileno filn);
+void storeSwapFileNumberSet(StoreEntry * e, sfileno filn);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeFsInit(void);
+void storeFsInit(void);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeFsDone(void);
+void storeFsDone(void);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeReplAdd(const char *, REMOVALPOLICYCREATE *);
+void storeReplAdd(const char *, REMOVALPOLICYCREATE *);
 
 /// \ingroup StoreAPI
 extern FREE destroyStoreEntry;
 
 /**
  \ingroup StoreAPI
  \todo should be a subclass of Packer perhaps ?
  */
-SQUIDCEXTERN void packerToStoreInit(Packer * p, StoreEntry * e);
+void packerToStoreInit(Packer * p, StoreEntry * e);
 
 /// \ingroup StoreAPI
-SQUIDCEXTERN void storeGetMemSpace(int size);
+void storeGetMemSpace(int size);
 
 #if _USE_INLINE_
 #include "Store.cci"
 #endif
 
 #endif /* SQUID_STORE_H */
