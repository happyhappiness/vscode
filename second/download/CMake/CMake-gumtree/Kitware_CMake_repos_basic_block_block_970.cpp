{
  // image_id's are integers, errors are negative. Add one just in case we
  //  get a valid image_id of zero (is that even possible?).
  image_id rc = load_add_on(libname.c_str());
  if (rc < 0) {
    last_dynamic_err = rc;
    return 0;
  }

  return rc + 1;
}