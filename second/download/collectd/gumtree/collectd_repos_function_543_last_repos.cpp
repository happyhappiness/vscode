static double abs_to_mean_sea_level_pressure(double abs_pressure) {
  double mean = -1.0;
  double temp = 0.0;
  int result = 0;

  if (config_normalize >= MSLP_DEU_WETT) {
    result = get_reference_temperature(&temp);
    if (result) {
      return NAN;
    }
  }

  switch (config_normalize) {
  case MSLP_NONE:
    mean = abs_pressure;
    break;

  case MSLP_INTERNATIONAL:
    mean = abs_pressure / pow(1.0 - 0.0065 * config_altitude / 288.15,
                              9.80665 * 0.0289644 / (8.31447 * 0.0065));
    break;

  case MSLP_DEU_WETT: {
    double E; /* humidity */
    double x;
    if (temp < 9.1)
      E = 5.6402 * (-0.0916 + exp(0.06 * temp));
    else
      E = 18.2194 * (1.0463 - exp(-0.0666 * temp));
    x = 9.80665 /
        (287.05 * (temp + 273.15 + 0.12 * E + 0.0065 * config_altitude / 2)) *
        config_altitude;
    mean = abs_pressure * exp(x);
  } break;

  default:
    ERROR(
        "barometer: abs_to_mean_sea_level_pressure: wrong conversion method %d",
        config_normalize);
    mean = abs_pressure;
    break;
  }

  DEBUG("barometer: abs_to_mean_sea_level_pressure: absPressure = %lf hPa, "
        "method = %d, meanPressure = %lf hPa",
        abs_pressure, config_normalize, mean);

  return mean;
}