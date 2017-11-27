static void BMP085_convert_adc_to_real(long adc_pressure, long adc_temperature,
                                       double *pressure, double *temperature)

{
  long X1, X2, X3;
  long B3, B5, B6;
  unsigned long B4, B7;

  long T;
  long P;

  /* calculate real temperature */
  X1 = ((adc_temperature - bmp085_AC6) * bmp085_AC5) >> 15;
  X2 = (bmp085_MC << 11) / (X1 + bmp085_MD);

  /* B5, T */
  B5 = X1 + X2;
  T = (B5 + 8) >> 4;
  *temperature = (double)T * 0.1;

  /* calculate real pressure */
  /* in general X1, X2, X3 are recycled while values of B3, B4, B5, B6 are kept
   */

  /* B6, B3 */
  B6 = B5 - 4000;
  X1 = ((bmp085_B2 * ((B6 * B6) >> 12)) >> 11);
  X2 = (((long)bmp085_AC2 * B6) >> 11);
  X3 = X1 + X2;
  B3 = (((((long)bmp085_AC1 * 4) + X3) << bmp085_oversampling) + 2) >> 2;

  /* B4 */
  X1 = (((long)bmp085_AC3 * B6) >> 13);
  X2 = (bmp085_B1 * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  B4 = ((long)bmp085_AC4 * (unsigned long)(X3 + 32768)) >> 15;

  /* B7, P */
  B7 = (unsigned long)(adc_pressure - B3) * (50000 >> bmp085_oversampling);
  if (B7 < 0x80000000) {
    P = (B7 << 1) / B4;
  } else {
    P = (B7 / B4) << 1;
  }
  X1 = (P >> 8) * (P >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = ((-7357) * P) >> 16;
  P = P + ((X1 + X2 + 3791) >> 4);

  *pressure = P / 100.0; // in [hPa]
  DEBUG("barometer: BMP085_convert_adc_to_real - got %lf hPa, %lf C", *pressure,
        *temperature);
}