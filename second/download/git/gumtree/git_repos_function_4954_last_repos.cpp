static void sha1_recompression_step(uint32_t step, uint32_t ihvin[5], uint32_t ihvout[5], const uint32_t me2[80], const uint32_t state[5])
{
	switch (step)
	{
#ifdef DOSTORESTATE0
	case 0:
		sha1recompress_fast_0(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE1
	case 1:
		sha1recompress_fast_1(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE2
	case 2:
		sha1recompress_fast_2(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE3
	case 3:
		sha1recompress_fast_3(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE4
	case 4:
		sha1recompress_fast_4(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE5
	case 5:
		sha1recompress_fast_5(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE6
	case 6:
		sha1recompress_fast_6(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE7
	case 7:
		sha1recompress_fast_7(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE8
	case 8:
		sha1recompress_fast_8(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE9
	case 9:
		sha1recompress_fast_9(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE10
	case 10:
		sha1recompress_fast_10(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE11
	case 11:
		sha1recompress_fast_11(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE12
	case 12:
		sha1recompress_fast_12(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE13
	case 13:
		sha1recompress_fast_13(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE14
	case 14:
		sha1recompress_fast_14(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE15
	case 15:
		sha1recompress_fast_15(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE16
	case 16:
		sha1recompress_fast_16(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE17
	case 17:
		sha1recompress_fast_17(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE18
	case 18:
		sha1recompress_fast_18(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE19
	case 19:
		sha1recompress_fast_19(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE20
	case 20:
		sha1recompress_fast_20(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE21
	case 21:
		sha1recompress_fast_21(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE22
	case 22:
		sha1recompress_fast_22(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE23
	case 23:
		sha1recompress_fast_23(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE24
	case 24:
		sha1recompress_fast_24(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE25
	case 25:
		sha1recompress_fast_25(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE26
	case 26:
		sha1recompress_fast_26(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE27
	case 27:
		sha1recompress_fast_27(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE28
	case 28:
		sha1recompress_fast_28(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE29
	case 29:
		sha1recompress_fast_29(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE30
	case 30:
		sha1recompress_fast_30(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE31
	case 31:
		sha1recompress_fast_31(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE32
	case 32:
		sha1recompress_fast_32(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE33
	case 33:
		sha1recompress_fast_33(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE34
	case 34:
		sha1recompress_fast_34(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE35
	case 35:
		sha1recompress_fast_35(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE36
	case 36:
		sha1recompress_fast_36(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE37
	case 37:
		sha1recompress_fast_37(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE38
	case 38:
		sha1recompress_fast_38(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE39
	case 39:
		sha1recompress_fast_39(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE40
	case 40:
		sha1recompress_fast_40(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE41
	case 41:
		sha1recompress_fast_41(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE42
	case 42:
		sha1recompress_fast_42(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE43
	case 43:
		sha1recompress_fast_43(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE44
	case 44:
		sha1recompress_fast_44(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE45
	case 45:
		sha1recompress_fast_45(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE46
	case 46:
		sha1recompress_fast_46(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE47
	case 47:
		sha1recompress_fast_47(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE48
	case 48:
		sha1recompress_fast_48(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE49
	case 49:
		sha1recompress_fast_49(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE50
	case 50:
		sha1recompress_fast_50(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE51
	case 51:
		sha1recompress_fast_51(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE52
	case 52:
		sha1recompress_fast_52(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE53
	case 53:
		sha1recompress_fast_53(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE54
	case 54:
		sha1recompress_fast_54(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE55
	case 55:
		sha1recompress_fast_55(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE56
	case 56:
		sha1recompress_fast_56(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE57
	case 57:
		sha1recompress_fast_57(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE58
	case 58:
		sha1recompress_fast_58(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE59
	case 59:
		sha1recompress_fast_59(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE60
	case 60:
		sha1recompress_fast_60(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE61
	case 61:
		sha1recompress_fast_61(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE62
	case 62:
		sha1recompress_fast_62(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE63
	case 63:
		sha1recompress_fast_63(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE64
	case 64:
		sha1recompress_fast_64(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE65
	case 65:
		sha1recompress_fast_65(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE66
	case 66:
		sha1recompress_fast_66(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE67
	case 67:
		sha1recompress_fast_67(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE68
	case 68:
		sha1recompress_fast_68(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE69
	case 69:
		sha1recompress_fast_69(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE70
	case 70:
		sha1recompress_fast_70(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE71
	case 71:
		sha1recompress_fast_71(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE72
	case 72:
		sha1recompress_fast_72(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE73
	case 73:
		sha1recompress_fast_73(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE74
	case 74:
		sha1recompress_fast_74(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE75
	case 75:
		sha1recompress_fast_75(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE76
	case 76:
		sha1recompress_fast_76(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE77
	case 77:
		sha1recompress_fast_77(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE78
	case 78:
		sha1recompress_fast_78(ihvin, ihvout, me2, state);
		break;
#endif
#ifdef DOSTORESTATE79
	case 79:
		sha1recompress_fast_79(ihvin, ihvout, me2, state);
		break;
#endif
	default:
		abort();
	}

}