; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/crc32_fast.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@lzma_crc32_table = external constant [8 x [256 x i32]], align 16

; Function Attrs: nounwind readonly uwtable
define i32 @lzma_crc32(i8* %buf, i64 %size, i32 %crc) #0 !dbg !14 {
entry:
  %buf.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %crc.addr = alloca i32, align 4
  %limit = alloca i8*, align 8
  %tmp = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !24, metadata !25), !dbg !26
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !27, metadata !25), !dbg !28
  store i32 %crc, i32* %crc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %crc.addr, metadata !29, metadata !25), !dbg !30
  %0 = load i32, i32* %crc.addr, align 4, !dbg !31
  %neg = xor i32 %0, -1, !dbg !32
  store i32 %neg, i32* %crc.addr, align 4, !dbg !33
  %1 = load i64, i64* %size.addr, align 8, !dbg !34
  %cmp = icmp ugt i64 %1, 8, !dbg !36
  br i1 %cmp, label %if.then, label %if.end, !dbg !37

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i8** %limit, metadata !38, metadata !25), !dbg !40
  br label %while.cond, !dbg !41

while.cond:                                       ; preds = %while.body, %if.then
  %2 = load i8*, i8** %buf.addr, align 8, !dbg !42
  %3 = ptrtoint i8* %2 to i64, !dbg !44
  %and = and i64 %3, 7, !dbg !45
  %tobool = icmp ne i64 %and, 0, !dbg !46
  br i1 %tobool, label %while.body, label %while.end, !dbg !46

while.body:                                       ; preds = %while.cond
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !47
  %incdec.ptr = getelementptr inbounds i8, i8* %4, i32 1, !dbg !47
  store i8* %incdec.ptr, i8** %buf.addr, align 8, !dbg !47
  %5 = load i8, i8* %4, align 1, !dbg !49
  %conv = zext i8 %5 to i32, !dbg !49
  %6 = load i32, i32* %crc.addr, align 4, !dbg !50
  %and1 = and i32 %6, 255, !dbg !50
  %xor = xor i32 %conv, %and1, !dbg !51
  %idxprom = zext i32 %xor to i64, !dbg !52
  %arrayidx = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom, !dbg !52
  %7 = load i32, i32* %arrayidx, align 4, !dbg !52
  %8 = load i32, i32* %crc.addr, align 4, !dbg !53
  %shr = lshr i32 %8, 8, !dbg !53
  %xor2 = xor i32 %7, %shr, !dbg !54
  store i32 %xor2, i32* %crc.addr, align 4, !dbg !55
  %9 = load i64, i64* %size.addr, align 8, !dbg !56
  %dec = add i64 %9, -1, !dbg !56
  store i64 %dec, i64* %size.addr, align 8, !dbg !56
  br label %while.cond, !dbg !57

while.end:                                        ; preds = %while.cond
  %10 = load i8*, i8** %buf.addr, align 8, !dbg !59
  %11 = load i64, i64* %size.addr, align 8, !dbg !60
  %and3 = and i64 %11, -8, !dbg !61
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 %and3, !dbg !62
  store i8* %add.ptr, i8** %limit, align 8, !dbg !63
  %12 = load i64, i64* %size.addr, align 8, !dbg !64
  %and4 = and i64 %12, 7, !dbg !64
  store i64 %and4, i64* %size.addr, align 8, !dbg !64
  br label %while.cond5, !dbg !65

while.cond5:                                      ; preds = %while.body8, %while.end
  %13 = load i8*, i8** %buf.addr, align 8, !dbg !66
  %14 = load i8*, i8** %limit, align 8, !dbg !67
  %cmp6 = icmp ult i8* %13, %14, !dbg !68
  br i1 %cmp6, label %while.body8, label %while.end47, !dbg !69

while.body8:                                      ; preds = %while.cond5
  call void @llvm.dbg.declare(metadata i32* %tmp, metadata !70, metadata !25), !dbg !72
  %15 = load i8*, i8** %buf.addr, align 8, !dbg !73
  %16 = bitcast i8* %15 to i32*, !dbg !74
  %17 = load i32, i32* %16, align 4, !dbg !74
  %18 = load i32, i32* %crc.addr, align 4, !dbg !75
  %xor9 = xor i32 %18, %17, !dbg !75
  store i32 %xor9, i32* %crc.addr, align 4, !dbg !75
  %19 = load i8*, i8** %buf.addr, align 8, !dbg !76
  %add.ptr10 = getelementptr inbounds i8, i8* %19, i64 4, !dbg !76
  store i8* %add.ptr10, i8** %buf.addr, align 8, !dbg !76
  %20 = load i32, i32* %crc.addr, align 4, !dbg !77
  %and11 = and i32 %20, 255, !dbg !77
  %idxprom12 = zext i32 %and11 to i64, !dbg !78
  %arrayidx13 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 7), i64 0, i64 %idxprom12, !dbg !78
  %21 = load i32, i32* %arrayidx13, align 4, !dbg !78
  %22 = load i32, i32* %crc.addr, align 4, !dbg !79
  %shr14 = lshr i32 %22, 8, !dbg !79
  %and15 = and i32 %shr14, 255, !dbg !79
  %idxprom16 = zext i32 %and15 to i64, !dbg !80
  %arrayidx17 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 6), i64 0, i64 %idxprom16, !dbg !80
  %23 = load i32, i32* %arrayidx17, align 4, !dbg !80
  %xor18 = xor i32 %21, %23, !dbg !81
  %24 = load i32, i32* %crc.addr, align 4, !dbg !82
  %shr19 = lshr i32 %24, 16, !dbg !82
  %and20 = and i32 %shr19, 255, !dbg !82
  %idxprom21 = zext i32 %and20 to i64, !dbg !83
  %arrayidx22 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 5), i64 0, i64 %idxprom21, !dbg !83
  %25 = load i32, i32* %arrayidx22, align 4, !dbg !83
  %xor23 = xor i32 %xor18, %25, !dbg !84
  %26 = load i32, i32* %crc.addr, align 4, !dbg !85
  %shr24 = lshr i32 %26, 24, !dbg !85
  %idxprom25 = zext i32 %shr24 to i64, !dbg !86
  %arrayidx26 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 4), i64 0, i64 %idxprom25, !dbg !86
  %27 = load i32, i32* %arrayidx26, align 4, !dbg !86
  %xor27 = xor i32 %xor23, %27, !dbg !87
  store i32 %xor27, i32* %crc.addr, align 4, !dbg !88
  %28 = load i8*, i8** %buf.addr, align 8, !dbg !89
  %29 = bitcast i8* %28 to i32*, !dbg !90
  %30 = load i32, i32* %29, align 4, !dbg !90
  store i32 %30, i32* %tmp, align 4, !dbg !91
  %31 = load i8*, i8** %buf.addr, align 8, !dbg !92
  %add.ptr28 = getelementptr inbounds i8, i8* %31, i64 4, !dbg !92
  store i8* %add.ptr28, i8** %buf.addr, align 8, !dbg !92
  %32 = load i32, i32* %tmp, align 4, !dbg !93
  %and29 = and i32 %32, 255, !dbg !93
  %idxprom30 = zext i32 %and29 to i64, !dbg !94
  %arrayidx31 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 3), i64 0, i64 %idxprom30, !dbg !94
  %33 = load i32, i32* %arrayidx31, align 4, !dbg !94
  %34 = load i32, i32* %tmp, align 4, !dbg !95
  %shr32 = lshr i32 %34, 8, !dbg !95
  %and33 = and i32 %shr32, 255, !dbg !95
  %idxprom34 = zext i32 %and33 to i64, !dbg !96
  %arrayidx35 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 2), i64 0, i64 %idxprom34, !dbg !96
  %35 = load i32, i32* %arrayidx35, align 4, !dbg !96
  %xor36 = xor i32 %33, %35, !dbg !97
  %36 = load i32, i32* %crc.addr, align 4, !dbg !98
  %xor37 = xor i32 %xor36, %36, !dbg !99
  %37 = load i32, i32* %tmp, align 4, !dbg !100
  %shr38 = lshr i32 %37, 16, !dbg !100
  %and39 = and i32 %shr38, 255, !dbg !100
  %idxprom40 = zext i32 %and39 to i64, !dbg !101
  %arrayidx41 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 1), i64 0, i64 %idxprom40, !dbg !101
  %38 = load i32, i32* %arrayidx41, align 4, !dbg !101
  %xor42 = xor i32 %xor37, %38, !dbg !102
  %39 = load i32, i32* %tmp, align 4, !dbg !103
  %shr43 = lshr i32 %39, 24, !dbg !103
  %idxprom44 = zext i32 %shr43 to i64, !dbg !104
  %arrayidx45 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom44, !dbg !104
  %40 = load i32, i32* %arrayidx45, align 4, !dbg !104
  %xor46 = xor i32 %xor42, %40, !dbg !105
  store i32 %xor46, i32* %crc.addr, align 4, !dbg !106
  br label %while.cond5, !dbg !107

while.end47:                                      ; preds = %while.cond5
  br label %if.end, !dbg !108

if.end:                                           ; preds = %while.end47, %entry
  br label %while.cond48, !dbg !109

while.cond48:                                     ; preds = %while.body52, %if.end
  %41 = load i64, i64* %size.addr, align 8, !dbg !110
  %dec49 = add i64 %41, -1, !dbg !110
  store i64 %dec49, i64* %size.addr, align 8, !dbg !110
  %cmp50 = icmp ne i64 %41, 0, !dbg !112
  br i1 %cmp50, label %while.body52, label %while.end61, !dbg !113

while.body52:                                     ; preds = %while.cond48
  %42 = load i8*, i8** %buf.addr, align 8, !dbg !114
  %incdec.ptr53 = getelementptr inbounds i8, i8* %42, i32 1, !dbg !114
  store i8* %incdec.ptr53, i8** %buf.addr, align 8, !dbg !114
  %43 = load i8, i8* %42, align 1, !dbg !115
  %conv54 = zext i8 %43 to i32, !dbg !115
  %44 = load i32, i32* %crc.addr, align 4, !dbg !116
  %and55 = and i32 %44, 255, !dbg !116
  %xor56 = xor i32 %conv54, %and55, !dbg !117
  %idxprom57 = zext i32 %xor56 to i64, !dbg !118
  %arrayidx58 = getelementptr inbounds [256 x i32], [256 x i32]* getelementptr inbounds ([8 x [256 x i32]], [8 x [256 x i32]]* @lzma_crc32_table, i64 0, i64 0), i64 0, i64 %idxprom57, !dbg !118
  %45 = load i32, i32* %arrayidx58, align 4, !dbg !118
  %46 = load i32, i32* %crc.addr, align 4, !dbg !119
  %shr59 = lshr i32 %46, 8, !dbg !119
  %xor60 = xor i32 %45, %shr59, !dbg !120
  store i32 %xor60, i32* %crc.addr, align 4, !dbg !121
  br label %while.cond48, !dbg !122

while.end61:                                      ; preds = %while.cond48
  %47 = load i32, i32* %crc.addr, align 4, !dbg !124
  %neg62 = xor i32 %47, -1, !dbg !125
  ret i32 %neg62, !dbg !126
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!21, !22}
!llvm.ident = !{!23}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !13)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/crc32_fast.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!14 = distinct !DISubprogram(name: "lzma_crc32", scope: !1, file: !1, line: 27, type: !15, isLocal: false, isDefinition: true, scopeLine: 28, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!15 = !DISubroutineType(types: !16)
!16 = !{!11, !17, !7, !11}
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !19)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !5, line: 48, baseType: !20)
!20 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!21 = !{i32 2, !"Dwarf Version", i32 4}
!22 = !{i32 2, !"Debug Info Version", i32 3}
!23 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!24 = !DILocalVariable(name: "buf", arg: 1, scope: !14, file: !1, line: 27, type: !17)
!25 = !DIExpression()
!26 = !DILocation(line: 27, column: 27, scope: !14)
!27 = !DILocalVariable(name: "size", arg: 2, scope: !14, file: !1, line: 27, type: !7)
!28 = !DILocation(line: 27, column: 39, scope: !14)
!29 = !DILocalVariable(name: "crc", arg: 3, scope: !14, file: !1, line: 27, type: !11)
!30 = !DILocation(line: 27, column: 54, scope: !14)
!31 = !DILocation(line: 29, column: 9, scope: !14)
!32 = !DILocation(line: 29, column: 8, scope: !14)
!33 = !DILocation(line: 29, column: 6, scope: !14)
!34 = !DILocation(line: 35, column: 6, scope: !35)
!35 = distinct !DILexicalBlock(scope: !14, file: !1, line: 35, column: 6)
!36 = !DILocation(line: 35, column: 11, scope: !35)
!37 = !DILocation(line: 35, column: 6, scope: !14)
!38 = !DILocalVariable(name: "limit", scope: !39, file: !1, line: 36, type: !17)
!39 = distinct !DILexicalBlock(scope: !35, file: !1, line: 35, column: 16)
!40 = !DILocation(line: 36, column: 19, scope: !39)
!41 = !DILocation(line: 40, column: 3, scope: !39)
!42 = !DILocation(line: 40, column: 22, scope: !43)
!43 = !DILexicalBlockFile(scope: !39, file: !1, discriminator: 1)
!44 = !DILocation(line: 40, column: 10, scope: !43)
!45 = !DILocation(line: 40, column: 27, scope: !43)
!46 = !DILocation(line: 40, column: 3, scope: !43)
!47 = !DILocation(line: 41, column: 34, scope: !48)
!48 = distinct !DILexicalBlock(scope: !39, file: !1, line: 40, column: 32)
!49 = !DILocation(line: 41, column: 30, scope: !48)
!50 = !DILocation(line: 41, column: 39, scope: !48)
!51 = !DILocation(line: 41, column: 37, scope: !48)
!52 = !DILocation(line: 41, column: 10, scope: !48)
!53 = !DILocation(line: 41, column: 49, scope: !48)
!54 = !DILocation(line: 41, column: 47, scope: !48)
!55 = !DILocation(line: 41, column: 8, scope: !48)
!56 = !DILocation(line: 42, column: 4, scope: !48)
!57 = !DILocation(line: 40, column: 3, scope: !58)
!58 = !DILexicalBlockFile(scope: !39, file: !1, discriminator: 2)
!59 = !DILocation(line: 46, column: 11, scope: !39)
!60 = !DILocation(line: 46, column: 18, scope: !39)
!61 = !DILocation(line: 46, column: 23, scope: !39)
!62 = !DILocation(line: 46, column: 15, scope: !39)
!63 = !DILocation(line: 46, column: 9, scope: !39)
!64 = !DILocation(line: 50, column: 8, scope: !39)
!65 = !DILocation(line: 53, column: 3, scope: !39)
!66 = !DILocation(line: 53, column: 10, scope: !43)
!67 = !DILocation(line: 53, column: 16, scope: !43)
!68 = !DILocation(line: 53, column: 14, scope: !43)
!69 = !DILocation(line: 53, column: 3, scope: !43)
!70 = !DILocalVariable(name: "tmp", scope: !71, file: !1, line: 54, type: !11)
!71 = distinct !DILexicalBlock(scope: !39, file: !1, line: 53, column: 23)
!72 = !DILocation(line: 54, column: 13, scope: !71)
!73 = !DILocation(line: 56, column: 31, scope: !71)
!74 = !DILocation(line: 56, column: 11, scope: !71)
!75 = !DILocation(line: 56, column: 8, scope: !71)
!76 = !DILocation(line: 57, column: 8, scope: !71)
!77 = !DILocation(line: 59, column: 30, scope: !71)
!78 = !DILocation(line: 59, column: 10, scope: !71)
!79 = !DILocation(line: 60, column: 30, scope: !71)
!80 = !DILocation(line: 60, column: 10, scope: !71)
!81 = !DILocation(line: 60, column: 8, scope: !71)
!82 = !DILocation(line: 61, column: 30, scope: !71)
!83 = !DILocation(line: 61, column: 10, scope: !71)
!84 = !DILocation(line: 61, column: 8, scope: !71)
!85 = !DILocation(line: 62, column: 30, scope: !71)
!86 = !DILocation(line: 62, column: 10, scope: !71)
!87 = !DILocation(line: 62, column: 8, scope: !71)
!88 = !DILocation(line: 59, column: 8, scope: !71)
!89 = !DILocation(line: 64, column: 30, scope: !71)
!90 = !DILocation(line: 64, column: 10, scope: !71)
!91 = !DILocation(line: 64, column: 8, scope: !71)
!92 = !DILocation(line: 65, column: 8, scope: !71)
!93 = !DILocation(line: 70, column: 30, scope: !71)
!94 = !DILocation(line: 70, column: 10, scope: !71)
!95 = !DILocation(line: 71, column: 30, scope: !71)
!96 = !DILocation(line: 71, column: 10, scope: !71)
!97 = !DILocation(line: 71, column: 8, scope: !71)
!98 = !DILocation(line: 72, column: 10, scope: !71)
!99 = !DILocation(line: 72, column: 8, scope: !71)
!100 = !DILocation(line: 73, column: 30, scope: !71)
!101 = !DILocation(line: 73, column: 10, scope: !71)
!102 = !DILocation(line: 73, column: 8, scope: !71)
!103 = !DILocation(line: 74, column: 30, scope: !71)
!104 = !DILocation(line: 74, column: 10, scope: !71)
!105 = !DILocation(line: 74, column: 8, scope: !71)
!106 = !DILocation(line: 70, column: 8, scope: !71)
!107 = !DILocation(line: 53, column: 3, scope: !58)
!108 = !DILocation(line: 76, column: 2, scope: !39)
!109 = !DILocation(line: 78, column: 2, scope: !14)
!110 = !DILocation(line: 78, column: 13, scope: !111)
!111 = !DILexicalBlockFile(scope: !14, file: !1, discriminator: 1)
!112 = !DILocation(line: 78, column: 16, scope: !111)
!113 = !DILocation(line: 78, column: 2, scope: !111)
!114 = !DILocation(line: 79, column: 33, scope: !14)
!115 = !DILocation(line: 79, column: 29, scope: !14)
!116 = !DILocation(line: 79, column: 38, scope: !14)
!117 = !DILocation(line: 79, column: 36, scope: !14)
!118 = !DILocation(line: 79, column: 9, scope: !14)
!119 = !DILocation(line: 79, column: 48, scope: !14)
!120 = !DILocation(line: 79, column: 46, scope: !14)
!121 = !DILocation(line: 79, column: 7, scope: !14)
!122 = !DILocation(line: 78, column: 2, scope: !123)
!123 = !DILexicalBlockFile(scope: !14, file: !1, discriminator: 2)
!124 = !DILocation(line: 85, column: 10, scope: !14)
!125 = !DILocation(line: 85, column: 9, scope: !14)
!126 = !DILocation(line: 85, column: 2, scope: !14)
