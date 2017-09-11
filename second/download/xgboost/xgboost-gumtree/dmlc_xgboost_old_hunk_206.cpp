}  // namespace utils
}  // namespace xgboost
#else
// thread interface using g++     
extern "C" {
#include <semaphore.h>
#include <pthread.h>
}
namespace xgboost {
namespace utils {
/*!\brief semaphore class */
class Semaphore {
  #ifdef __APPLE__
 private:
  sem_t* semPtr;
  char sema_name[20];            
 private:
  inline void GenRandomString(char *s, const int len) {
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" ;
    for (int i = 0; i < len; ++i) {
      s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    s[len] = 0;
  }
 public:
  inline void Init(int init_val) {
    sema_name[0]='/'; 
    sema_name[1]='s'; 
    sema_name[2]='e'; 
    sema_name[3]='/'; 
    GenRandomString(&sema_name[4], 16);
    if((semPtr = sem_open(sema_name, O_CREAT, 0644, init_val)) == SEM_FAILED) {
      perror("sem_open");
      exit(1);
    }
    utils::Assert(semPtr != NULL, "create Semaphore error");
  }
  inline void Destroy(void) {
    if (sem_close(semPtr) == -1) {
