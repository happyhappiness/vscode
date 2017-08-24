{
  if (SystemTools::FileExists(filename)) {
    // If isFile is set return not FileIsDirectory,
    // so this will only be true if it is a file
    return !isFile || !SystemTools::FileIsDirectory(filename);
  }
  return false;
}