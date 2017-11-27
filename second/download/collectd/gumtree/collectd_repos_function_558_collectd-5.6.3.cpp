static void BMP085_adjust_oversampling(void) {
  int new_val = 0;

  if (config_oversample > 6) /* 8 */
  {
    new_val = 8;
    bmp085_oversampling = 3;
    bmp085_cmdCnvPress = BMP085_CMD_CONVERT_PRESS_3;
    bmp085_timeCnvPress = BMP085_TIME_CNV_PRESS_3;
  } else if (config_oversample > 3) /* 4 */
  {
    new_val = 4;
    bmp085_oversampling = 2;
    bmp085_cmdCnvPress = BMP085_CMD_CONVERT_PRESS_2;
    bmp085_timeCnvPress = BMP085_TIME_CNV_PRESS_2;
  } else if (config_oversample > 1) /* 2 */
  {
    new_val = 2;
    bmp085_oversampling = 1;
    bmp085_cmdCnvPress = BMP085_CMD_CONVERT_PRESS_1;
    bmp085_timeCnvPress = BMP085_TIME_CNV_PRESS_1;
  } else /* 1 */
  {
    new_val = 1;
    bmp085_oversampling = 0;
    bmp085_cmdCnvPress = BMP085_CMD_CONVERT_PRESS_0;
    bmp085_timeCnvPress = BMP085_TIME_CNV_PRESS_0;
  }

  DEBUG("barometer: BMP085_adjust_oversampling - correcting oversampling from "
        "%d to %d",
        config_oversample, new_val);
  config_oversample = new_val;
}