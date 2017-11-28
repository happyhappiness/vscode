main(argc, argv)
{
    int i;

    fm = file_map_create(TEST_SIZE);

    for (i = 0; i < TEST_SIZE; ++i) {
        file_map_bit_set(i);
        assert(file_map_bit_test(i));
        file_map_bit_reset(i);
    }
}