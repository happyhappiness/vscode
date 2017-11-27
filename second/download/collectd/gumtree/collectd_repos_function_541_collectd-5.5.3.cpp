static int MPL3115_detect(void)
{
    __s32 res;
    char errbuf[1024];

    if (ioctl(i2c_bus_fd, I2C_SLAVE_FORCE, MPL3115_I2C_ADDRESS) < 0)
    {
        ERROR("barometer: MPL3115_detect problem setting i2c slave address to 0x%02X: %s",
              MPL3115_I2C_ADDRESS,
              sstrerror (errno, errbuf, sizeof (errbuf)));
        return 0 ;
    }

    res = i2c_smbus_read_byte_data(i2c_bus_fd, MPL3115_REG_WHO_AM_I);
    if(res == MPL3115_WHO_AM_I_RESP)
    {
        DEBUG ("barometer: MPL3115_detect - positive detection");
        return 1;
    }

    DEBUG ("barometer: MPL3115_detect - negative detection");
    return 0;
}