static int MPL3115_init_sensor(void)
{
    __s32 res;
    __s8 offset;
    char errbuf[1024];

    /* Reset the sensor. It will reset immediately without ACKing */
    /* the transaction, so no error handling here. */
    i2c_smbus_write_byte_data(i2c_bus_fd,
                              MPL3115_REG_CTRL_REG1,
                              MPL3115_CTRL_REG1_RST);

    /* wait some time for the reset to finish */
    usleep(100000);

    /* now it should be in standby already so we can go and configure it */

    /*  Set temperature offset. */
    /*  result = ADCtemp + offset [C] */
    offset = (__s8) (config_temp_offset * 16.0);
    res = i2c_smbus_write_byte_data(i2c_bus_fd, MPL3115_REG_OFF_T, offset);
    if (res < 0)
    {
        ERROR ("barometer: MPL3115_init_sensor - problem setting temp offset: %s",
               sstrerror (errno, errbuf, sizeof (errbuf)));
        return -1;
    }

    /*  Set pressure offset. */
    /*  result = ADCpress + offset [hPa] */
    offset = (__s8) (config_press_offset * 100.0 / 4.0);
    res = i2c_smbus_write_byte_data(i2c_bus_fd, MPL3115_REG_OFF_P, offset);
    if (res < 0)
    {
        ERROR ("barometer: MPL3115_init_sensor - problem setting pressure offset: %s",
               sstrerror (errno, errbuf, sizeof (errbuf)));
        return -1;
    }

    /* Enable Data Flags in PT_DATA_CFG - flags on both pressure and temp */
    res = i2c_smbus_write_byte_data(i2c_bus_fd,
                                    MPL3115_REG_PT_DATA_CFG,
                                    MPL3115_PT_DATA_DREM        \
                                    | MPL3115_PT_DATA_PDEF      \
                                    | MPL3115_PT_DATA_TDEF);
    if (res < 0)
    {
        ERROR ("barometer: MPL3115_init_sensor - problem setting PT_DATA_CFG: %s",
               sstrerror (errno, errbuf, sizeof (errbuf)));
        return -1;
    }

    /* Set to barometer with an OSR */
    res = i2c_smbus_write_byte_data(i2c_bus_fd,
                                    MPL3115_REG_CTRL_REG1,
                                    mpl3115_oversample);
    if (res < 0)
    {
        ERROR ("barometer: MPL3115_init_sensor - problem configuring CTRL_REG1: %s",
               sstrerror (errno, errbuf, sizeof (errbuf)));
        return -1;
    }

    return 0;
}