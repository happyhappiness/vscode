};

/// \ingroup StoreAPI
typedef RefCount<Store> StorePointer;

/// \ingroup StoreAPI
size_t storeEntryInUse();

/// \ingroup StoreAPI
const char *storeEntryFlags(const StoreEntry *);

/// \ingroup StoreAPI
void storeEntryReplaceObject(StoreEntry *, HttpReply *);

/// \ingroup StoreAPI
StoreEntry *storeGetPublic(const char *uri, const HttpRequestMethod& method);

/// \ingroup StoreAPI
StoreEntry *storeGetPublicByRequest(HttpRequest * request);

/// \ingroup StoreAPI
StoreEntry *storeGetPublicByRequestMethod(HttpRequest * request, const HttpRequestMethod& method);

/// \ingroup StoreAPI
StoreEntry *storeCreateEntry(const char *, const char *, const RequestFlags &, const HttpRequestMethod&);

/// \ingroup StoreAPI
void storeInit(void);

/// \ingroup StoreAPI
void storeConfigure(void);

/// \ingroup StoreAPI
void storeFreeMemory(void);

/// \ingroup StoreAPI
int expiresMoreThan(time_t, time_t);

/// \ingroup StoreAPI
void storeAppendPrintf(StoreEntry *, const char *,...) PRINTF_FORMAT_ARG2;

/// \ingroup StoreAPI
void storeAppendVPrintf(StoreEntry *, const char *, va_list ap);

/// \ingroup StoreAPI
int storeTooManyDiskFilesOpen(void);

class SwapDir;
/// \ingroup StoreAPI
void storeHeapPositionUpdate(StoreEntry *, SwapDir *);

/// \ingroup StoreAPI
void storeSwapFileNumberSet(StoreEntry * e, sfileno filn);

/// \ingroup StoreAPI
void storeFsInit(void);

/// \ingroup StoreAPI
void storeFsDone(void);

/// \ingroup StoreAPI
void storeReplAdd(const char *, REMOVALPOLICYCREATE *);

/// \ingroup StoreAPI
extern FREE destroyStoreEntry;

/**
 \ingroup StoreAPI
 \todo should be a subclass of Packer perhaps ?
 */
void packerToStoreInit(Packer * p, StoreEntry * e);

/// \ingroup StoreAPI
void storeGetMemSpace(int size);

#if _USE_INLINE_
#include "Store.cci"
#endif

#endif /* SQUID_STORE_H */
