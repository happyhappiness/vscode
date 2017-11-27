static int nfs_config(const char *key, const char *value) {
  if (strcasecmp(key, "ReportV2") == 0)
    report_v2 = IS_TRUE(value);
  else if (strcasecmp(key, "ReportV3") == 0)
    report_v3 = IS_TRUE(value);
  else if (strcasecmp(key, "ReportV4") == 0)
    report_v4 = IS_TRUE(value);
  else
    return -1;

  return 0;
}