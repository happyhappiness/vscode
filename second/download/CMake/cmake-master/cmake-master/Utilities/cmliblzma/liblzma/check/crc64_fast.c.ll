; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/crc64_fast.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@lzma_crc64_table = external constant [4 x [256 x i64]], align 16

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_crc64(i8* %buf, i64 %size, i64 %crc) #0 !dbg !14 {
entry:
  %buf.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %crc.addr = alloca i64, align 8
  %limit = alloca i8*, align 8
  %tmp = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !25, metadata !26), !dbg !27
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !28, metadata !26), !dbg !29
  store i64 %crc, i64* %crc.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %crc.addr, metadata !30, metadata !26), !dbg !31
  %0 = load i64, i64* %crc.addr, align 8, !dbg !32
  %neg = xor i64 %0, -1, !dbg !33
  store i64 %neg, i64* %crc.addr, align 8, !dbg !34
  %1 = load i64, i64* %size.addr, align 8, !dbg !35
  %cmp = icmp ugt i64 %1, 4, !dbg !37
  br i1 %cmp, label %if.then, label %if.end, !dbg !38

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %limit, metadata !39, metadata !26), !dbg !41
  br label %while.cond, !dbg !42

while.cond:                                       ; preds = %while.body, %if.then
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !43
  %3 = ptrtoint i8* %2 to i64, !dbg !45
  %and = and i64 %3, 3, !dbg !46
  %tobool = icmp ne i64 %and, 0, !dbg !47
  br i1 %tobool, label %while.body, label %while.end, !dbg !47

while.body:                                       ; preds = %while.cond
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !48
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 1, !dbg !48
  store i8* %incdec.ptr, i8** %buf.addr, align 8, !dbg !48
  %5 = load i8, i8* %4, align 1, !dbg !50
  %conv = zext i8 %5 to i64, !dbg !50
  %6 = load i64, i64* %crc.addr, align 8, !dbg !51
  %and1 = and i64 %6, 255, !dbg !51
  %xor = xor i64 %conv, %and1, !dbg !52
  %arrayidx = getelementptr inbounds [256 x i64], [256 x i64]* getelementptr inbounds ([4 x [256 x i64]], [4 x [256 x i64]]* @lzma_crc64_table, i64 0, i64 0), i64 0, i64 %xor, !dbg !53
  %7 = load i64, i64* %arrayidx, align 8, !dbg !53
  %8 = load i64, i64* %crc.addr, align 8, !dbg !54
  %shr = lshr i64 %8, 8, !dbg !54
  %xor2 = xor i64 %7, %shr, !dbg !55
  store i64 %xor2, i64* %crc.addr, align 8, !dbg !56
  %9 = load i64, i64* %size.addr, align 8, !dbg !57
  %dec = add i64 %9, -1, !dbg !57
  store i64 %dec, i64* %size.addr, align 8, !dbg !57
  br label %while.cond, !dbg !58

while.end:                                        ; preds = %while.cond
  %10 = load i8*, i8** %buf.addr, align 8, !dbg !60
  %11 = load i64, i64* %size.addr, align 8, !dbg !61
  %and3 = and i64 %11, -4, !dbg !62
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 %and3, !dbg !63
  store i8* %add.ptr, i8** %limit, align 8, !dbg !64
  %12 = load i64, i64* %size.addr, align 8, !dbg !65
  %and4 = and i64 %12, 3, !dbg !65
  store i64 %and4, i64* %size.addr, align 8, !dbg !65
  br label %while.cond5, !dbg !66

while.cond5:                                      ; preds = %while.body8, %while.end
  %13 = load i8*, i8** %buf.addr, align 8, !dbg !67
  %14 = load i8*, i8** %limit, align 8, !dbg !68
  %cmp6 = icmp ult i8* %13, %14, !dbg !69
  br i1 %cmp6, label %while.body8, label %while.end31, !dbg !70

while.body8:                                      ; preds = %while.cond5
  call void @llvm.dbg.declare(metadata i32* %tmp, metadata !71, metadata !26), !dbg !73
  %15 = load i64, i64* %crc.addr, align 8, !dbg !74
  %16 = load i8*, i8** %buf.addr, align 8, !dbg !75
  %17 = bitcast i8* %16 to i32*, !dbg !76
  %18 = load i32, i32* %17, align 4, !dbg !76
  %conv9 = zext i32 %18 to i64, !dbg !76
  %xor10 = xor i64 %15, %conv9, !dbg !77
  %conv11 = trunc i64 %xor10 to i32, !dbg !74
  store i32 %conv11, i32* %tmp, align 4, !dbg !73
  %19 = load i8*, i8** %buf.addr, align 8, !dbg !78
  %add.ptr12 = getelementptr inbounds i8, i8* %19, i64 4, !dbg !78
  store i8* %add.ptr12, i8** %buf.addr, align 8, !dbg !78
  %20 = load i32, i32* %tmp, align 4, !dbg !79
  %and13 = and i32 %20, 255, !dbg !79
  %idxprom = zext i32 %and13 to i64, !dbg !80
  %arrayidx14 = getelementptr inbounds [256 x i64], [256 x i64]* getelementptr inbounds ([4 x [256 x i64]], [4 x [256 x i64]]* @lzma_crc64_table, i64 0, i64 3), i64 0, i64 %idxprom, !dbg !80
  %21 = load i64, i64* %arrayidx14, align 8, !dbg !80
  %22 = load i32, i32* %tmp, align 4, !dbg !81
  %shr15 = lshr i32 %22, 8, !dbg !81
  %and16 = and i32 %shr15, 255, !dbg !81
  %idxprom17 = zext i32 %and16 to i64, !dbg !82
  %arrayidx18 = getelementptr inbounds [256 x i64], [256 x i64]* getelementptr inbounds ([4 x [256 x i64]], [4 x [256 x i64]]* @lzma_crc64_table, i64 0, i64 2), i64 0, i64 %idxprom17, !dbg !82
  %23 = load i64, i64* %arrayidx18, align 8, !dbg !82
  %xor19 = xor i64 %21, %23, !dbg !83
  %24 = load i64, i64* %crc.addr, align 8, !dbg !84
  %shr20 = lshr i64 %24, 32, !dbg !84
  %xor21 = xor i64 %xor19, %shr20, !dbg !85
  %25 = load i32, i32* %tmp, align 4, !dbg !86
  %shr22 = lshr i32 %25, 16, !dbg !86
  %and23 = and i32 %shr22, 255, !dbg !86
  %idxprom24 = zext i32 %and23 to i64, !dbg !87
  %arrayidx25 = getelementptr inbounds [256 x i64], [256 x i64]* getelementptr inbounds ([4 x [256 x i64]], [4 x [256 x i64]]* @lzma_crc64_table, i64 0, i64 1), i64 0, i64 %idxprom24, !dbg !87
  %26 = load i64, i64* %arrayidx25, align 8, !dbg !87
  %xor26 = xor i64 %xor21, %26, !dbg !88
  %27 = load i32, i32* %tmp, align 4, !dbg !89
  %shr27 = lshr i32 %27, 24, !dbg !89
  %idxprom28 = zext i32 %shr27 to i64, !dbg !90
  %arrayidx29 = getelementptr inbounds [256 x i64], [256 x i64]* getelementptr inbounds ([4 x [256 x i64]], [4 x [256 x i64]]* @lzma_crc64_table, i64 0, i64 0), i64 0, i64 %idxprom28, !dbg !90
  %28 = load i64, i64* %arrayidx29, align 8, !dbg !90
  %xor30 = xor i64 %xor26, %28, !dbg !91
  store i64 %xor30, i64* %crc.addr, align 8, !dbg !92
  br label %while.cond5, !dbg !93

while.end31:                                      ; preds = %while.cond5
  br label %if.end, !dbg !94

if.end:                                           ; preds = %while.end31, %entry
  br label %while.cond32, !dbg !95

while.cond32:                                     ; preds = %while.body36, %if.end
  %29 = load i64, i64* %size.addr, align 8, !dbg !96
  %dec33 = add i64 %29, -1, !dbg !96
  store i64 %dec33, i64* %size.addr, align 8, !dbg !96
  %cmp34 = icmp ne i64 %29, 0, !dbg !98
  br i1 %cmp34, label %while.body36, label %while.end44, !dbg !99

while.body36:                                     ; preds = %while.cond32
  %30 = load i8*, i8** %buf.addr, align 8, !dbg !100
  %incdec.ptr37 = getelementptr inbounds i8, i8* %30, i32 1, !dbg !100
  store i8* %incdec.ptr37, i8** %buf.addr, align 8, !dbg !100
  %31 = load i8, i8* %30, align 1, !dbg !101
  %conv38 = zext i8 %31 to i64, !dbg !101
  %32 = load i64, i64* %crc.addr, align 8, !dbg !102
  %and39 = and i64 %32, 255, !dbg !102
  %xor40 = xor i64 %conv38, %and39, !dbg !103
  %arrayidx41 = getelementptr inbounds [256 x i64], [256 x i64]* getelementptr inbounds ([4 x [256 x i64]], [4 x [256 x i64]]* @lzma_crc64_table, i64 0, i64 0), i64 0, i64 %xor40, !dbg !104
  %33 = load i64, i64* %arrayidx41, align 8, !dbg !104
  %34 = load i64, i64* %crc.addr, align 8, !dbg !105
  %shr42 = lshr i64 %34, 8, !dbg !105
  %xor43 = xor i64 %33, %shr42, !dbg !106
  store i64 %xor43, i64* %crc.addr, align 8, !dbg !107
  br label %while.cond32, !dbg !108

while.end44:                                      ; preds = %while.cond32
  %35 = load i64, i64* %crc.addr, align 8, !dbg !110
  %neg45 = xor i64 %35, -1, !dbg !111
  ret i64 %neg45, !dbg !112
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!22, !23}
!llvm.ident = !{!24}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !13)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/crc64_fast.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{}
!3 = !{!4, !7, !9}
!4 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !5, line: 122, baseType: !6)
!5 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!6 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !8, line: 62, baseType: !6)
!8 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !11)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !5, line: 51, baseType: !12)
!12 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!13 = !{!14}
!14 = distinct !DISubprogram(name: "lzma_crc64", scope: !1, file: !1, line: 30, type: !15, isLocal: false, isDefinition: true, scopeLine: 31, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{!17, !18, !7, !17}
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !5, line: 55, baseType: !6)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !5, line: 48, baseType: !21)
!21 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!22 = !{i32 2, !"Dwarf Version", i32 4}
!23 = !{i32 2, !"Debug Info Version", i32 3}
!24 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!25 = !DILocalVariable(name: "buf", arg: 1, scope: !14, file: !1, line: 30, type: !18)
!26 = !DIExpression()
!27 = !DILocation(line: 30, column: 27, scope: !14)
!28 = !DILocalVariable(name: "size", arg: 2, scope: !14, file: !1, line: 30, type: !7)
!29 = !DILocation(line: 30, column: 39, scope: !14)
!30 = !DILocalVariable(name: "crc", arg: 3, scope: !14, file: !1, line: 30, type: !17)
!31 = !DILocation(line: 30, column: 54, scope: !14)
!32 = !DILocation(line: 32, column: 9, scope: !14)
!33 = !DILocation(line: 32, column: 8, scope: !14)
!34 = !DILocation(line: 32, column: 6, scope: !14)
!35 = !DILocation(line: 38, column: 6, scope: !36)
!36 = distinct !DILexicalBlock(scope: !14, file: !1, line: 38, column: 6)
!37 = !DILocation(line: 38, column: 11, scope: !36)
!38 = !DILocation(line: 38, column: 6, scope: !14)
!39 = !DILocalVariable(name: "limit", scope: !40, file: !1, line: 39, type: !18)
!40 = distinct !DILexicalBlock(scope: !36, file: !1, line: 38, column: 16)
!41 = !DILocation(line: 39, column: 18, scope: !40)
!42 = !DILocation(line: 41, column: 3, scope: !40)
!43 = !DILocation(line: 41, column: 22, scope: !44)
!44 = !DILexicalBlockFile(scope: !40, file: !1, discriminator: 1)
!45 = !DILocation(line: 41, column: 10, scope: !44)
!46 = !DILocation(line: 41, column: 27, scope: !44)
!47 = !DILocation(line: 41, column: 3, scope: !44)
!48 = !DILocation(line: 42, column: 34, scope: !49)
!49 = distinct !DILexicalBlock(scope: !40, file: !1, line: 41, column: 32)
!50 = !DILocation(line: 42, column: 30, scope: !49)
!51 = !DILocation(line: 42, column: 39, scope: !49)
!52 = !DILocation(line: 42, column: 37, scope: !49)
!53 = !DILocation(line: 42, column: 10, scope: !49)
!54 = !DILocation(line: 42, column: 50, scope: !49)
!55 = !DILocation(line: 42, column: 48, scope: !49)
!56 = !DILocation(line: 42, column: 8, scope: !49)
!57 = !DILocation(line: 43, column: 4, scope: !49)
!58 = !DILocation(line: 41, column: 3, scope: !59)
!59 = !DILexicalBlockFile(scope: !40, file: !1, discriminator: 2)
!60 = !DILocation(line: 46, column: 11, scope: !40)
!61 = !DILocation(line: 46, column: 18, scope: !40)
!62 = !DILocation(line: 46, column: 23, scope: !40)
!63 = !DILocation(line: 46, column: 15, scope: !40)
!64 = !DILocation(line: 46, column: 9, scope: !40)
!65 = !DILocation(line: 47, column: 8, scope: !40)
!66 = !DILocation(line: 49, column: 3, scope: !40)
!67 = !DILocation(line: 49, column: 10, scope: !44)
!68 = !DILocation(line: 49, column: 16, scope: !44)
!69 = !DILocation(line: 49, column: 14, scope: !44)
!70 = !DILocation(line: 49, column: 3, scope: !44)
!71 = !DILocalVariable(name: "tmp", scope: !72, file: !1, line: 54, type: !10)
!72 = distinct !DILexicalBlock(scope: !40, file: !1, line: 49, column: 23)
!73 = !DILocation(line: 54, column: 19, scope: !72)
!74 = !DILocation(line: 54, column: 25, scope: !72)
!75 = !DILocation(line: 54, column: 51, scope: !72)
!76 = !DILocation(line: 54, column: 31, scope: !72)
!77 = !DILocation(line: 54, column: 29, scope: !72)
!78 = !DILocation(line: 56, column: 8, scope: !72)
!79 = !DILocation(line: 58, column: 30, scope: !72)
!80 = !DILocation(line: 58, column: 10, scope: !72)
!81 = !DILocation(line: 59, column: 30, scope: !72)
!82 = !DILocation(line: 59, column: 10, scope: !72)
!83 = !DILocation(line: 59, column: 8, scope: !72)
!84 = !DILocation(line: 60, column: 10, scope: !72)
!85 = !DILocation(line: 60, column: 8, scope: !72)
!86 = !DILocation(line: 61, column: 30, scope: !72)
!87 = !DILocation(line: 61, column: 10, scope: !72)
!88 = !DILocation(line: 61, column: 8, scope: !72)
!89 = !DILocation(line: 62, column: 30, scope: !72)
!90 = !DILocation(line: 62, column: 10, scope: !72)
!91 = !DILocation(line: 62, column: 8, scope: !72)
!92 = !DILocation(line: 58, column: 8, scope: !72)
!93 = !DILocation(line: 49, column: 3, scope: !59)
!94 = !DILocation(line: 64, column: 2, scope: !40)
!95 = !DILocation(line: 66, column: 2, scope: !14)
!96 = !DILocation(line: 66, column: 13, scope: !97)
!97 = !DILexicalBlockFile(scope: !14, file: !1, discriminator: 1)
!98 = !DILocation(line: 66, column: 16, scope: !97)
!99 = !DILocation(line: 66, column: 2, scope: !97)
!100 = !DILocation(line: 67, column: 33, scope: !14)
!101 = !DILocation(line: 67, column: 29, scope: !14)
!102 = !DILocation(line: 67, column: 38, scope: !14)
!103 = !DILocation(line: 67, column: 36, scope: !14)
!104 = !DILocation(line: 67, column: 9, scope: !14)
!105 = !DILocation(line: 67, column: 49, scope: !14)
!106 = !DILocation(line: 67, column: 47, scope: !14)
!107 = !DILocation(line: 67, column: 7, scope: !14)
!108 = !DILocation(line: 66, column: 2, scope: !109)
!109 = !DILexicalBlockFile(scope: !14, file: !1, discriminator: 2)
!110 = !DILocation(line: 73, column: 10, scope: !14)
!111 = !DILocation(line: 73, column: 9, scope: !14)
!112 = !DILocation(line: 73, column: 2, scope: !14)
