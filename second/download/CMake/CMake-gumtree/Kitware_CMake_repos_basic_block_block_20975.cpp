{
    err = 0;
    *tid = thread;
    ctx->self = thread;
    ResumeThread(thread);
  }