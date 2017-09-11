  }
  inline void Post(void) {
    sem_post(semPtr);
  }               
  #else
 private:
  sem_t sem;
 public:
  inline void Init(int init_val) {
    sem_init(&sem, 0, init_val);
  }
  inline void Destroy(void) {
    sem_destroy(&sem);
  }
  inline void Wait(void) {
    sem_wait(&sem);
  }
  inline void Post(void) {
    sem_post(&sem);
  }
  #endif  
};

// helper for c thread
// used to strictly call c++ function from pthread
struct ThreadContext {
  void *(*entry)(void*);
  void *param;
};
extern "C" {
  inline void *RunThreadContext(void *ctx_) {
    ThreadContext *ctx = reinterpret_cast<ThreadContext*>(ctx_);
    void *ret = (*ctx->entry)(ctx->param);
    delete ctx;
    return ret;
  }
}
/*!\brief simple thread class */
class Thread {
 private:
  pthread_t thread;                

 public :
  inline void Start(void *entry(void*), void *param) {
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    ThreadContext *ctx = new ThreadContext();
    ctx->entry = entry; ctx->param = param;
    pthread_create(&thread, &attr, RunThreadContext, ctx);
  }
  inline int Join(void) {
    void *status;
