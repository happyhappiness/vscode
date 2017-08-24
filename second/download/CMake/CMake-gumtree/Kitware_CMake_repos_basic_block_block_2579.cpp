{
  // Call a CoreFoundation function...
  //
  CFBundleRef br = CFBundleGetMainBundle();
  (void)br;

  int res1 = findBundleFile(exec, "Resources/randomResourceFile.plist");
  int res2 = findBundleFile(exec, "MacOS/SomeRandomFile.txt");
  int res3 = findBundleFile(exec, "MacOS/README.rst");
  if (!res1 || !res2 || !res3) {
    return 1;
  }

  return 0;
}