{
  if (this->Filename.empty()) {
    return cmFileLockResult::MakeOk();
  }
  const int lockResult = this->LockFile(F_SETLK, F_UNLCK);

  this->Filename = "";

  ::close(this->File);
  this->File = -1;

  if (lockResult == 0) {
    return cmFileLockResult::MakeOk();
  }
  return cmFileLockResult::MakeSystem();
}