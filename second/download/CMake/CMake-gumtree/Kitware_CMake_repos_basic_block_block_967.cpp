{
  NSObjectFileImageReturnCode rc;
  NSObjectFileImage image = 0;

  rc = NSCreateObjectFileImageFromFile(libname.c_str(), &image);
  // rc == NSObjectFileImageInappropriateFile when trying to load a dylib file
  if (rc != NSObjectFileImageSuccess) {
    return 0;
  }
  NSModule handle =
    NSLinkModule(image, libname.c_str(), NSLINKMODULE_OPTION_BINDNOW |
                   NSLINKMODULE_OPTION_RETURN_ON_ERROR);
  NSDestroyObjectFileImage(image);
  return handle;
}