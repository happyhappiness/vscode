static double wireless_percent_to_power(double quality) {
  assert((quality >= 0.0) && (quality <= 100.0));

  return (quality * (POWER_MAX - POWER_MIN)) + POWER_MIN;
}