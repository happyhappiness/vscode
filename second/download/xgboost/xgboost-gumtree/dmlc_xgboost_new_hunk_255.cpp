/*!
 * Copyright by Contributors
 * \file thread.h
 * \brief this header include the minimum necessary resource
 * for multi-threading that can be compiled in windows, linux, mac
 * \author Tianqi Chen
 */
#ifndef XGBOOST_UTILS_THREAD_H_ // NOLINT(*)
#define XGBOOST_UTILS_THREAD_H_ // NOLINT(*)

#ifdef _MSC_VER
#include <windows.h>
#include <process.h>
#include "../xgboost/utils.h"
namespace xgboost {
namespace utils {
/*! \brief simple semaphore used for synchronization */
class Semaphore {
 public :
  inline void Init(int init_val) {
    sem = CreateSemaphore(NULL, init_val, 10, NULL);
    utils::Check(sem != NULL, "create Semaphore error");
  }
  inline void Destroy(void) {
    CloseHandle(sem);
  }
  inline void Wait(void) {
    utils::Check(WaitForSingleObject(sem, INFINITE) == WAIT_OBJECT_0, "WaitForSingleObject error");
  }
  inline void Post(void) {
    utils::Check(ReleaseSemaphore(sem, 1, NULL) != 0, "ReleaseSemaphore error");
  }

 private:
  HANDLE sem;
};

/*! \brief mutex under windows */
class Mutex {
 public:
  inline void Init(void) {
    utils::Check(InitializeCriticalSectionAndSpinCount(&mutex, 0x00000400) != 0,
                   "Mutex::Init fail");
  }
  inline void Lock(void) {
    EnterCriticalSection(&mutex);
  }
  inline void Unlock(void) {
    LeaveCriticalSection(&mutex);
  }
  inline void Destroy(void) {
    DeleteCriticalSection(&mutex);
  }

 private:
  friend class ConditionVariable;
  CRITICAL_SECTION mutex;
};

// conditional variable that uses pthread
class ConditionVariable {
 public:
  // initialize conditional variable
  inline void Init(void) {
    InitializeConditionVariable(&cond);
  }
  // destroy the thread
  inline void Destroy(void) {
    // DeleteConditionVariable(&cond);
  }
  // wait on the conditional variable
  inline void Wait(Mutex *mutex) {
    utils::Check(SleepConditionVariableCS(&cond, &(mutex->mutex), INFINITE) != 0,
                 "ConditionVariable:Wait fail");
  }
  inline void Broadcast(void) {
    WakeAllConditionVariable(&cond);
  }
  inline void Signal(void) {
    WakeConditionVariable(&cond);
  }

 private:
  CONDITION_VARIABLE cond;
};

/*! \brief simple thread that wraps windows thread */
class Thread {
 private:
  HANDLE    thread_handle;
  unsigned  thread_id;
 public:
  inline void Start(unsigned int __stdcall entry(void*p), void *param) {
    thread_handle = (HANDLE)_beginthreadex(NULL, 0, entry, param, 0, &thread_id);
  }
  inline int Join(void) {
    WaitForSingleObject(thread_handle, INFINITE);
    return 0;
