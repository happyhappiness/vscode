static int gettimeofday(struct timeval *tp, void *nothing)
{
#ifdef WITHOUT_MM_LIB
  SYSTEMTIME st;
  time_t tt;
  struct tm tmtm;
  /* mktime converts local to UTC */
  GetLocalTime (&st);
  tmtm.tm_sec = st.wSecond;
  tmtm.tm_min = st.wMinute;
  tmtm.tm_hour = st.wHour;
  tmtm.tm_mday = st.wDay;
  tmtm.tm_mon = st.wMonth - 1;
  tmtm.tm_year = st.wYear - 1900;
  tmtm.tm_isdst = -1;
  tt = mktime (&tmtm);
  tp->tv_sec = tt;
  tp->tv_usec = st.wMilliseconds * 1000;
#else
  /**
   ** The earlier time calculations using GetLocalTime
   ** had a time resolution of 10ms.The timeGetTime, part
   ** of multimedia apis offer a better time resolution
   ** of 1ms.Need to link against winmm.lib for this
   **/
  unsigned long Ticks = 0;
  unsigned long Sec =0;
  unsigned long Usec = 0;
  Ticks = timeGetTime();

  Sec = Ticks/1000;
  Usec = (Ticks - (Sec*1000))*1000;
  tp->tv_sec = Sec;
  tp->tv_usec = Usec;
#endif /* WITHOUT_MM_LIB */
  (void)nothing;
  return 0;
}