static void MPL115_convert_adc_to_real(double   adc_pressure,
                                       double   adc_temp,
                                       double * pressure,
                                       double * temperature)
{
    double Pcomp;
    Pcomp = mpl115_coeffA0 +                                            \
        (mpl115_coeffB1 + mpl115_coeffC11*adc_pressure + mpl115_coeffC12*adc_temp) * adc_pressure + \
        (mpl115_coeffB2 + mpl115_coeffC22*adc_temp) * adc_temp;

    *pressure = ((1150.0-500.0) * Pcomp / 1023.0) + 500.0;
    *temperature = (472.0 - adc_temp) / 5.35 + 25.0;
    DEBUG ("barometer: MPL115_convert_adc_to_real - got %lf hPa, %lf C",
           *pressure,
           *temperature);
}