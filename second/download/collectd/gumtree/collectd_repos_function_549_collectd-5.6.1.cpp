static int MPL115_read_coeffs(void)
{
    uint8_t mpl115_coeffs[MPL115_NUM_COEFFS] = { 0 };
    int32_t res;

    int8_t  sia0MSB, sia0LSB, sib1MSB, sib1LSB, sib2MSB, sib2LSB;
    int8_t  sic12MSB, sic12LSB, sic11MSB, sic11LSB, sic22MSB, sic22LSB;
    int16_t sia0, sib1, sib2, sic12, sic11, sic22;

    char errbuf[1024];

    res = i2c_smbus_read_i2c_block_data(i2c_bus_fd,
                                        MPL115_ADDR_COEFFS,
                                        STATIC_ARRAY_SIZE (mpl115_coeffs),
                                        mpl115_coeffs);
    if (res < 0)
    {
        ERROR ("barometer: MPL115_read_coeffs - problem reading data: %s",
               sstrerror (errno, errbuf, sizeof (errbuf)));
        return -1;
    }

    /* Using perhaps less elegant/efficient code, but more readable. */
    /* a0: 16total 1sign 12int 4fract 0pad */
    sia0MSB = mpl115_coeffs[0];
    sia0LSB = mpl115_coeffs[1];
    sia0 = (int16_t) sia0MSB <<8;          /* s16 type, Shift to MSB */
    sia0 += (int16_t) sia0LSB & 0x00FF;    /* Add LSB to 16bit number */
    mpl115_coeffA0 = (double) (sia0);
    mpl115_coeffA0 /= 8.0;                 /* 3 fract bits */

    /* b1: 16total 1sign 2int 13fract 0pad */
    sib1MSB= mpl115_coeffs[2];
    sib1LSB= mpl115_coeffs[3];
    sib1 = sib1MSB <<8;                    /* Shift to MSB */
    sib1 += sib1LSB & 0x00FF;              /* Add LSB to 16bit number */
    mpl115_coeffB1 = (double) (sib1);
    mpl115_coeffB1 /= 8192.0;              /* 13 fract */

    /* b2: 16total 1sign 1int 14fract 0pad */
    sib2MSB= mpl115_coeffs[4];
    sib2LSB= mpl115_coeffs[5];
    sib2 = sib2MSB <<8;                     /* Shift to MSB */
    sib2 += sib2LSB & 0x00FF;               /* Add LSB to 16bit number */
    mpl115_coeffB2 = (double) (sib2);
    mpl115_coeffB2 /= 16384.0;              /* 14 fract */

    /* c12: 14total 1sign 0int 13fract 9pad */
    sic12MSB= mpl115_coeffs[6];
    sic12LSB= mpl115_coeffs[7];
    sic12 = sic12MSB <<8;                   /* Shift to MSB only by 8 for MSB */
    sic12 += sic12LSB & 0x00FF;
    mpl115_coeffC12 = (double) (sic12);
    mpl115_coeffC12 /= 4.0;                 /* 16-14=2 */
    mpl115_coeffC12 /= 4194304.0;           /* 13+9=22 fract */

    /* c11: 11total 1sign 0int 11fract 11pad */
    sic11MSB= mpl115_coeffs[8];
    sic11LSB= mpl115_coeffs[9];
    sic11 = sic11MSB <<8;                   /* Shift to MSB only by 8 for MSB */
    sic11 += sic11LSB & 0x00FF;
    mpl115_coeffC11 = (double) (sic11);
    mpl115_coeffC11 /= 32.0;               /* 16-11=5 */
    mpl115_coeffC11 /= 4194304.0;          /* 11+11=22 fract */

    /* c12: 11total 1sign 0int 10fract 15pad */
    sic22MSB= mpl115_coeffs[10];
    sic22LSB= mpl115_coeffs[11];
    sic22 = sic22MSB <<8;                   /* Shift to MSB only by 8 for MSB */
    sic22 += sic22LSB & 0x00FF;
    mpl115_coeffC22 = (double) (sic22);
    mpl115_coeffC22 /= 32.0; //16-11=5
    mpl115_coeffC22 /= 33554432.0;          /* 10+15=25 fract */

    DEBUG("barometer: MPL115_read_coeffs: a0=%lf, b1=%lf, b2=%lf, c12=%lf, c11=%lf, c22=%lf",
          mpl115_coeffA0,
          mpl115_coeffB1,
          mpl115_coeffB2,
          mpl115_coeffC12,
          mpl115_coeffC11,
          mpl115_coeffC22);
    return 0;
}