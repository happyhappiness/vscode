static int collectd_barometer_init (void)
{
    char errbuf[1024];

    DEBUG ("barometer: collectd_barometer_init");

    if (config_device == NULL)
    {
        ERROR("barometer: collectd_barometer_init I2C bus device not configured");
        return -1;
    }

    if (config_normalize >= MSLP_INTERNATIONAL && isnan(config_altitude))
    {
        ERROR("barometer: collectd_barometer_init no altitude configured " \
              "for mean sea level pressure normalization.");
        return -1;
    }

    if (config_normalize == MSLP_DEU_WETT
        &&
        temp_list == NULL)
    {
        ERROR("barometer: collectd_barometer_init no temperature reference "\
              "configured for mean sea level pressure normalization.");
        return -1;
    }


    i2c_bus_fd = open(config_device, O_RDWR);
    if (i2c_bus_fd < 0)
    {
        ERROR ("barometer: collectd_barometer_init problem opening I2C bus device \"%s\": %s (is loaded mod i2c-dev?)",
               config_device,
               sstrerror (errno, errbuf, sizeof (errbuf)));
        return -1;
    }

    /* detect sensor type - this will also set slave address */
    sensor_type = detect_sensor_type();

    /* init correct sensor type */
    switch(sensor_type)
    {
/* MPL3115 */
    case Sensor_MPL3115:
    {
        MPL3115_adjust_oversampling();

        if(MPL3115_init_sensor())
            return -1;

        plugin_register_read ("barometer", MPL3115_collectd_barometer_read);
    }
    break;

/* MPL115 */
    case Sensor_MPL115:
    {
        if (averaging_create (&pressure_averaging, config_oversample))
        {
            ERROR("barometer: collectd_barometer_init pressure averaging init failed");
            return -1;
        }

        if (averaging_create (&temperature_averaging, config_oversample))
        {
            ERROR("barometer: collectd_barometer_init temperature averaging init failed");
            return -1;
        }

        if (MPL115_read_coeffs() < 0)
            return -1;

        plugin_register_read ("barometer", MPL115_collectd_barometer_read);
    }
    break;

/* BMP085 */
    case Sensor_BMP085:
    {
        BMP085_adjust_oversampling();

        if (BMP085_read_coeffs() < 0)
            return -1;

        plugin_register_read ("barometer", BMP085_collectd_barometer_read);
    }
    break;

/* anything else -> error */
    default:
        ERROR("barometer: collectd_barometer_init - no supported sensor found");
        return -1;
    }


    configured = 1;
    return 0;
}