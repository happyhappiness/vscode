#ifndef XGBOOST_UTILS_THREAD_H
#define XGBOOST_UTILS_THREAD_H
/*!
 * \file thread.h
 * \brief this header include the minimum necessary resource for multi-threading
 * \author Tianqi Chen
 * Acknowledgement: this file is adapted from SVDFeature project, by same author. 
 *  The MAC support part of this code is provided by Artemy Kolchinsky
 */
#ifdef _MSC_VER
#include "utils.h"
#include <windows.h>
#include <process.h>
namespace xgboost {
namespace utils {
/*! \brief simple semaphore used for synchronization */
class Semaphore {
 public :
  inline void Init(int init_val) {
    sem = CreateSemaphore(NULL, init_val, 10, NULL);
    utils::Assert(sem != NULL, "create Semaphore error");
  }
  inline void Destroy(void) {
    CloseHandle(sem);
  }
  inline void Wait(void) {
    utils::Assert(WaitForSingleObject(sem, INFINITE) == WAIT_OBJECT_0, "WaitForSingleObject error");
  }
  inline void Post(void) {
    utils::Assert(ReleaseSemaphore(sem, 1, NULL)  != 0, "ReleaseSemaphore error");
  }
 private:
  HANDLE sem;
};
/*! \brief simple thread that wraps windows thread */
class Thread {
 private:
  HANDLE    thread_handle;
  unsigned  thread_id;            
 public:
  inline void Start(unsigned int __stdcall entry(void*), void *param) {
    thread_handle = (HANDLE)_beginthreadex(NULL, 0, entry, param, 0, &thread_id);
  }            
  inline int Join(void) {
    WaitForSingleObject(thread_handle, INFINITE);
    return 0;
