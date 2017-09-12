serverLog(LL_WARNING|LL_RAW,
                "\n------ DUMPING CODE AROUND EIP ------\n"
                "Symbol: %s (base: %p)\n"
                "Module: %s (base %p)\n"
                "$ xxd -r -p /tmp/dump.hex /tmp/dump.bin\n"
                "$ objdump --adjust-vma=%p -D -b binary -m i386:x86-64 /tmp/dump.bin\n"
                "------\n",
                info.dli_sname, info.dli_saddr, info.dli_fname, info.dli_fbase,
                info.dli_saddr);