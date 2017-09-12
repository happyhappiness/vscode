
int main(void) {
    {
        sds x = sdsnew("foo");

        /* SDS creation and length */
        test_cond("Can create a string and obtain the length",
            sdslen(x) == 3 && memcmp(x,"foo",3) == 0)

        /* Nul term checking */
        test_cond("The string contains the nul term", x[3] == '\0')
    }
    test_report()
}
