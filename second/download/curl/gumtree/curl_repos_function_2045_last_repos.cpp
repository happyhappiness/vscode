NETDB_DEFINE_CONTEXT
/* Make the CLIB Inet stuff link */
#include <netinet/in.h>
#include <arpa/inet.h>
NETINET_DEFINE_CONTEXT

int netware_init(void)
{
  int rc = 0;
  unsigned int myHandle = GetNLMHandle();
  /* import UnAugmentAsterisk dynamically for NW4.x compatibility */
  void (*pUnAugmentAsterisk)(int) = (void(*)(int))
          ImportSymbol(myHandle, "UnAugmentAsterisk");
  /* import UseAccurateCaseForPaths dynamically for NW3.x compatibility */
  void (*pUseAccurateCaseForPaths)(int) = (void(*)(int))
          ImportSymbol(myHandle, "UseAccurateCaseForPaths");
  if(pUnAugmentAsterisk)
    pUnAugmentAsterisk(1);
  if(pUseAccurateCaseForPaths)
    pUseAccurateCaseForPaths(1);
  UnimportSymbol(myHandle, "UnAugmentAsterisk");
  UnimportSymbol(myHandle, "UseAccurateCaseForPaths");
  /* set long name space */
  if((SetCurrentNameSpace(4) == 255)) {
    rc = 1;
  }
  if((SetTargetNameSpace(4) == 255)) {
    rc = rc + 2;
  }
  return rc;
}