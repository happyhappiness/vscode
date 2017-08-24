(perms) {
    if (!SystemTools::SetPermissions(real_destination, perm)) {
      return false;
    }
  }