printf("Got signal %d, faulty address is %p, from %p\n", sig, info->si_addr, 
		   (void *)uc->uc_mcontext.gregs[REG_EIP]);