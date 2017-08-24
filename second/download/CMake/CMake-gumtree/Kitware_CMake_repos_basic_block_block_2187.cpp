(!SystemTools::GetPermissions(source, mode) ||
      !SystemTools::SetPermissions(source, S_IWRITE)) {
    SetLastError(err);
    return false;
  }