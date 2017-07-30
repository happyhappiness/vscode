; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @lzma_vli_decode(i64* noalias %vli, i64* %vli_pos, i8* noalias %in, i64* noalias %in_pos, i64 %in_size) #0 !dbg !26 {
entry:
  %retval = alloca i32, align 4
  %vli.addr = alloca i64*, align 8
  %vli_pos.addr = alloca i64*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %vli_pos_internal = alloca i64, align 8
  %byte = alloca i8, align 1
  store i64* %vli, i64** %vli.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %vli.addr, metadata !45, metadata !46), !dbg !47
  store i64* %vli_pos, i64** %vli_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %vli_pos.addr, metadata !48, metadata !46), !dbg !49
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !50, metadata !46), !dbg !51
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !52, metadata !46), !dbg !53
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !54, metadata !46), !dbg !55
  call void @llvm.dbg.declare(metadata i64* %vli_pos_internal, metadata !56, metadata !46), !dbg !57
  store i64 0, i64* %vli_pos_internal, align 8, !dbg !57
  %0 = load i64*, i64** %vli_pos.addr, align 8, !dbg !58
  %cmp = icmp eq i64* %0, null, !dbg !60
  br i1 %cmp, label %if.then, label %if.else, !dbg !61

if.then:                                          ; preds = %entry
  store i64* %vli_pos_internal, i64** %vli_pos.addr, align 8, !dbg !62
  %1 = load i64*, i64** %vli.addr, align 8, !dbg !64
  store i64 0, i64* %1, align 8, !dbg !65
  %2 = load i64*, i64** %in_pos.addr, align 8, !dbg !66
  %3 = load i64, i64* %2, align 8, !dbg !68
  %4 = load i64, i64* %in_size.addr, align 8, !dbg !69
  %cmp1 = icmp uge i64 %3, %4, !dbg !70
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !71

if.then2:                                         ; preds = %if.then
  store i32 9, i32* %retval, align 4, !dbg !72
  br label %return, !dbg !72

if.end:                                           ; preds = %if.then
  br label %if.end13, !dbg !73

if.else:                                          ; preds = %entry
  %5 = load i64*, i64** %vli_pos.addr, align 8, !dbg !74
  %6 = load i64, i64* %5, align 8, !dbg !77
  %cmp3 = icmp eq i64 %6, 0, !dbg !78
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !79

if.then4:                                         ; preds = %if.else
  %7 = load i64*, i64** %vli.addr, align 8, !dbg !80
  store i64 0, i64* %7, align 8, !dbg !81
  br label %if.end5, !dbg !82

if.end5:                                          ; preds = %if.then4, %if.else
  %8 = load i64*, i64** %vli_pos.addr, align 8, !dbg !83
  %9 = load i64, i64* %8, align 8, !dbg !85
  %cmp6 = icmp uge i64 %9, 9, !dbg !86
  br i1 %cmp6, label %if.then8, label %lor.lhs.false, !dbg !87

lor.lhs.false:                                    ; preds = %if.end5
  %10 = load i64*, i64** %vli.addr, align 8, !dbg !88
  %11 = load i64, i64* %10, align 8, !dbg !90
  %12 = load i64*, i64** %vli_pos.addr, align 8, !dbg !91
  %13 = load i64, i64* %12, align 8, !dbg !92
  %mul = mul i64 %13, 7, !dbg !93
  %shr = lshr i64 %11, %mul, !dbg !94
  %cmp7 = icmp ne i64 %shr, 0, !dbg !95
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !96

if.then8:                                         ; preds = %lor.lhs.false, %if.end5
  store i32 11, i32* %retval, align 4, !dbg !98
  br label %return, !dbg !98

if.end9:                                          ; preds = %lor.lhs.false
  %14 = load i64*, i64** %in_pos.addr, align 8, !dbg !99
  %15 = load i64, i64* %14, align 8, !dbg !101
  %16 = load i64, i64* %in_size.addr, align 8, !dbg !102
  %cmp10 = icmp uge i64 %15, %16, !dbg !103
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !104

if.then11:                                        ; preds = %if.end9
  store i32 10, i32* %retval, align 4, !dbg !105
  br label %return, !dbg !105

if.end12:                                         ; preds = %if.end9
  br label %if.end13

if.end13:                                         ; preds = %if.end12, %if.end
  br label %do.body, !dbg !106

do.body:                                          ; preds = %do.cond, %if.end13
  call void @llvm.dbg.declare(metadata i8* %byte, metadata !107, metadata !46), !dbg !109
  %17 = load i64*, i64** %in_pos.addr, align 8, !dbg !110
  %18 = load i64, i64* %17, align 8, !dbg !111
  %19 = load i8*, i8** %in.addr, align 8, !dbg !112
  %arrayidx = getelementptr inbounds i8, i8* %19, i64 %18, !dbg !112
  %20 = load i8, i8* %arrayidx, align 1, !dbg !112
  store i8 %20, i8* %byte, align 1, !dbg !109
  %21 = load i64*, i64** %in_pos.addr, align 8, !dbg !113
  %22 = load i64, i64* %21, align 8, !dbg !114
  %inc = add i64 %22, 1, !dbg !114
  store i64 %inc, i64* %21, align 8, !dbg !114
  %23 = load i8, i8* %byte, align 1, !dbg !115
  %conv = zext i8 %23 to i32, !dbg !115
  %and = and i32 %conv, 127, !dbg !116
  %conv14 = sext i32 %and to i64, !dbg !117
  %24 = load i64*, i64** %vli_pos.addr, align 8, !dbg !118
  %25 = load i64, i64* %24, align 8, !dbg !119
  %mul15 = mul i64 %25, 7, !dbg !120
  %shl = shl i64 %conv14, %mul15, !dbg !121
  %26 = load i64*, i64** %vli.addr, align 8, !dbg !122
  %27 = load i64, i64* %26, align 8, !dbg !123
  %add = add i64 %27, %shl, !dbg !123
  store i64 %add, i64* %26, align 8, !dbg !123
  %28 = load i64*, i64** %vli_pos.addr, align 8, !dbg !124
  %29 = load i64, i64* %28, align 8, !dbg !125
  %inc16 = add i64 %29, 1, !dbg !125
  store i64 %inc16, i64* %28, align 8, !dbg !125
  %30 = load i8, i8* %byte, align 1, !dbg !126
  %conv17 = zext i8 %30 to i32, !dbg !126
  %and18 = and i32 %conv17, 128, !dbg !128
  %cmp19 = icmp eq i32 %and18, 0, !dbg !129
  br i1 %cmp19, label %if.then21, label %if.end31, !dbg !130

if.then21:                                        ; preds = %do.body
  %31 = load i8, i8* %byte, align 1, !dbg !131
  %conv22 = zext i8 %31 to i32, !dbg !131
  %cmp23 = icmp eq i32 %conv22, 0, !dbg !134
  br i1 %cmp23, label %land.lhs.true, label %if.end28, !dbg !135

land.lhs.true:                                    ; preds = %if.then21
  %32 = load i64*, i64** %vli_pos.addr, align 8, !dbg !136
  %33 = load i64, i64* %32, align 8, !dbg !138
  %cmp25 = icmp ugt i64 %33, 1, !dbg !139
  br i1 %cmp25, label %if.then27, label %if.end28, !dbg !140

if.then27:                                        ; preds = %land.lhs.true
  store i32 9, i32* %retval, align 4, !dbg !141
  br label %return, !dbg !141

if.end28:                                         ; preds = %land.lhs.true, %if.then21
  %34 = load i64*, i64** %vli_pos.addr, align 8, !dbg !142
  %cmp29 = icmp eq i64* %34, %vli_pos_internal, !dbg !143
  %cond = select i1 %cmp29, i32 0, i32 1, !dbg !142
  store i32 %cond, i32* %retval, align 4, !dbg !144
  br label %return, !dbg !144

if.end31:                                         ; preds = %do.body
  %35 = load i64*, i64** %vli_pos.addr, align 8, !dbg !145
  %36 = load i64, i64* %35, align 8, !dbg !147
  %cmp32 = icmp eq i64 %36, 9, !dbg !148
  br i1 %cmp32, label %if.then34, label %if.end35, !dbg !149

if.then34:                                        ; preds = %if.end31
  store i32 9, i32* %retval, align 4, !dbg !150
  br label %return, !dbg !150

if.end35:                                         ; preds = %if.end31
  br label %do.cond, !dbg !151

do.cond:                                          ; preds = %if.end35
  %37 = load i64*, i64** %in_pos.addr, align 8, !dbg !152
  %38 = load i64, i64* %37, align 8, !dbg !154
  %39 = load i64, i64* %in_size.addr, align 8, !dbg !155
  %cmp36 = icmp ult i64 %38, %39, !dbg !156
  br i1 %cmp36, label %do.body, label %do.end, !dbg !157

do.end:                                           ; preds = %do.cond
  %40 = load i64*, i64** %vli_pos.addr, align 8, !dbg !158
  %cmp38 = icmp eq i64* %40, %vli_pos_internal, !dbg !159
  %cond40 = select i1 %cmp38, i32 9, i32 0, !dbg !158
  store i32 %cond40, i32* %retval, align 4, !dbg !160
  br label %return, !dbg !160

return:                                           ; preds = %do.end, %if.then34, %if.end28, %if.then27, %if.then11, %if.then8, %if.then2
  %41 = load i32, i32* %retval, align 4, !dbg !161
  ret i32 %41, !dbg !161
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!42, !43}
!llvm.ident = !{!44}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !25)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 57, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "LZMA_OK", value: 0)
!7 = !DIEnumerator(name: "LZMA_STREAM_END", value: 1)
!8 = !DIEnumerator(name: "LZMA_NO_CHECK", value: 2)
!9 = !DIEnumerator(name: "LZMA_UNSUPPORTED_CHECK", value: 3)
!10 = !DIEnumerator(name: "LZMA_GET_CHECK", value: 4)
!11 = !DIEnumerator(name: "LZMA_MEM_ERROR", value: 5)
!12 = !DIEnumerator(name: "LZMA_MEMLIMIT_ERROR", value: 6)
!13 = !DIEnumerator(name: "LZMA_FORMAT_ERROR", value: 7)
!14 = !DIEnumerator(name: "LZMA_OPTIONS_ERROR", value: 8)
!15 = !DIEnumerator(name: "LZMA_DATA_ERROR", value: 9)
!16 = !DIEnumerator(name: "LZMA_BUF_ERROR", value: 10)
!17 = !DIEnumerator(name: "LZMA_PROG_ERROR", value: 11)
!18 = !{!19, !20}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !21, line: 63, baseType: !22)
!21 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !23, line: 55, baseType: !24)
!23 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!24 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!25 = !{!26}
!26 = distinct !DISubprogram(name: "lzma_vli_decode", scope: !1, file: !1, line: 17, type: !27, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !41)
!27 = !DISubroutineType(types: !28)
!28 = !{!29, !30, !32, !35, !40, !33}
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!30 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !31)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !34, line: 62, baseType: !24)
!34 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!35 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !36)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !38)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !23, line: 48, baseType: !39)
!39 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!40 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !32)
!41 = !{}
!42 = !{i32 2, !"Dwarf Version", i32 4}
!43 = !{i32 2, !"Debug Info Version", i32 3}
!44 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!45 = !DILocalVariable(name: "vli", arg: 1, scope: !26, file: !1, line: 17, type: !30)
!46 = !DIExpression()
!47 = !DILocation(line: 17, column: 41, scope: !26)
!48 = !DILocalVariable(name: "vli_pos", arg: 2, scope: !26, file: !1, line: 17, type: !32)
!49 = !DILocation(line: 17, column: 54, scope: !26)
!50 = !DILocalVariable(name: "in", arg: 3, scope: !26, file: !1, line: 18, type: !35)
!51 = !DILocation(line: 18, column: 32, scope: !26)
!52 = !DILocalVariable(name: "in_pos", arg: 4, scope: !26, file: !1, line: 18, type: !40)
!53 = !DILocation(line: 18, column: 58, scope: !26)
!54 = !DILocalVariable(name: "in_size", arg: 5, scope: !26, file: !1, line: 19, type: !33)
!55 = !DILocation(line: 19, column: 10, scope: !26)
!56 = !DILocalVariable(name: "vli_pos_internal", scope: !26, file: !1, line: 22, type: !33)
!57 = !DILocation(line: 22, column: 9, scope: !26)
!58 = !DILocation(line: 23, column: 6, scope: !59)
!59 = distinct !DILexicalBlock(scope: !26, file: !1, line: 23, column: 6)
!60 = !DILocation(line: 23, column: 14, scope: !59)
!61 = !DILocation(line: 23, column: 6, scope: !26)
!62 = !DILocation(line: 24, column: 11, scope: !63)
!63 = distinct !DILexicalBlock(scope: !59, file: !1, line: 23, column: 23)
!64 = !DILocation(line: 25, column: 4, scope: !63)
!65 = !DILocation(line: 25, column: 8, scope: !63)
!66 = !DILocation(line: 31, column: 8, scope: !67)
!67 = distinct !DILexicalBlock(scope: !63, file: !1, line: 31, column: 7)
!68 = !DILocation(line: 31, column: 7, scope: !67)
!69 = !DILocation(line: 31, column: 18, scope: !67)
!70 = !DILocation(line: 31, column: 15, scope: !67)
!71 = !DILocation(line: 31, column: 7, scope: !63)
!72 = !DILocation(line: 32, column: 4, scope: !67)
!73 = !DILocation(line: 34, column: 2, scope: !63)
!74 = !DILocation(line: 36, column: 8, scope: !75)
!75 = distinct !DILexicalBlock(scope: !76, file: !1, line: 36, column: 7)
!76 = distinct !DILexicalBlock(scope: !59, file: !1, line: 34, column: 9)
!77 = !DILocation(line: 36, column: 7, scope: !75)
!78 = !DILocation(line: 36, column: 16, scope: !75)
!79 = !DILocation(line: 36, column: 7, scope: !76)
!80 = !DILocation(line: 37, column: 5, scope: !75)
!81 = !DILocation(line: 37, column: 9, scope: !75)
!82 = !DILocation(line: 37, column: 4, scope: !75)
!83 = !DILocation(line: 40, column: 8, scope: !84)
!84 = distinct !DILexicalBlock(scope: !76, file: !1, line: 40, column: 7)
!85 = !DILocation(line: 40, column: 7, scope: !84)
!86 = !DILocation(line: 40, column: 16, scope: !84)
!87 = !DILocation(line: 41, column: 5, scope: !84)
!88 = !DILocation(line: 41, column: 10, scope: !89)
!89 = !DILexicalBlockFile(scope: !84, file: !1, discriminator: 1)
!90 = !DILocation(line: 41, column: 9, scope: !89)
!91 = !DILocation(line: 41, column: 19, scope: !89)
!92 = !DILocation(line: 41, column: 18, scope: !89)
!93 = !DILocation(line: 41, column: 27, scope: !89)
!94 = !DILocation(line: 41, column: 14, scope: !89)
!95 = !DILocation(line: 41, column: 33, scope: !89)
!96 = !DILocation(line: 40, column: 7, scope: !97)
!97 = !DILexicalBlockFile(scope: !76, file: !1, discriminator: 1)
!98 = !DILocation(line: 42, column: 4, scope: !84)
!99 = !DILocation(line: 44, column: 8, scope: !100)
!100 = distinct !DILexicalBlock(scope: !76, file: !1, line: 44, column: 7)
!101 = !DILocation(line: 44, column: 7, scope: !100)
!102 = !DILocation(line: 44, column: 18, scope: !100)
!103 = !DILocation(line: 44, column: 15, scope: !100)
!104 = !DILocation(line: 44, column: 7, scope: !76)
!105 = !DILocation(line: 45, column: 4, scope: !100)
!106 = !DILocation(line: 48, column: 2, scope: !26)
!107 = !DILocalVariable(name: "byte", scope: !108, file: !1, line: 51, type: !37)
!108 = distinct !DILexicalBlock(scope: !26, file: !1, line: 48, column: 5)
!109 = !DILocation(line: 51, column: 17, scope: !108)
!110 = !DILocation(line: 51, column: 28, scope: !108)
!111 = !DILocation(line: 51, column: 27, scope: !108)
!112 = !DILocation(line: 51, column: 24, scope: !108)
!113 = !DILocation(line: 52, column: 6, scope: !108)
!114 = !DILocation(line: 52, column: 3, scope: !108)
!115 = !DILocation(line: 55, column: 22, scope: !108)
!116 = !DILocation(line: 55, column: 27, scope: !108)
!117 = !DILocation(line: 55, column: 11, scope: !108)
!118 = !DILocation(line: 55, column: 40, scope: !108)
!119 = !DILocation(line: 55, column: 39, scope: !108)
!120 = !DILocation(line: 55, column: 48, scope: !108)
!121 = !DILocation(line: 55, column: 35, scope: !108)
!122 = !DILocation(line: 55, column: 4, scope: !108)
!123 = !DILocation(line: 55, column: 8, scope: !108)
!124 = !DILocation(line: 56, column: 6, scope: !108)
!125 = !DILocation(line: 56, column: 3, scope: !108)
!126 = !DILocation(line: 59, column: 8, scope: !127)
!127 = distinct !DILexicalBlock(scope: !108, file: !1, line: 59, column: 7)
!128 = !DILocation(line: 59, column: 13, scope: !127)
!129 = !DILocation(line: 59, column: 21, scope: !127)
!130 = !DILocation(line: 59, column: 7, scope: !108)
!131 = !DILocation(line: 63, column: 8, scope: !132)
!132 = distinct !DILexicalBlock(scope: !133, file: !1, line: 63, column: 8)
!133 = distinct !DILexicalBlock(scope: !127, file: !1, line: 59, column: 27)
!134 = !DILocation(line: 63, column: 13, scope: !132)
!135 = !DILocation(line: 63, column: 21, scope: !132)
!136 = !DILocation(line: 63, column: 25, scope: !137)
!137 = !DILexicalBlockFile(scope: !132, file: !1, discriminator: 1)
!138 = !DILocation(line: 63, column: 24, scope: !137)
!139 = !DILocation(line: 63, column: 33, scope: !137)
!140 = !DILocation(line: 63, column: 8, scope: !137)
!141 = !DILocation(line: 64, column: 5, scope: !132)
!142 = !DILocation(line: 66, column: 11, scope: !133)
!143 = !DILocation(line: 66, column: 19, scope: !133)
!144 = !DILocation(line: 66, column: 4, scope: !133)
!145 = !DILocation(line: 80, column: 8, scope: !146)
!146 = distinct !DILexicalBlock(scope: !108, file: !1, line: 80, column: 7)
!147 = !DILocation(line: 80, column: 7, scope: !146)
!148 = !DILocation(line: 80, column: 16, scope: !146)
!149 = !DILocation(line: 80, column: 7, scope: !108)
!150 = !DILocation(line: 81, column: 4, scope: !146)
!151 = !DILocation(line: 83, column: 2, scope: !108)
!152 = !DILocation(line: 83, column: 12, scope: !153)
!153 = !DILexicalBlockFile(scope: !26, file: !1, discriminator: 1)
!154 = !DILocation(line: 83, column: 11, scope: !153)
!155 = !DILocation(line: 83, column: 21, scope: !153)
!156 = !DILocation(line: 83, column: 19, scope: !153)
!157 = !DILocation(line: 83, column: 2, scope: !153)
!158 = !DILocation(line: 85, column: 9, scope: !26)
!159 = !DILocation(line: 85, column: 17, scope: !26)
!160 = !DILocation(line: 85, column: 2, scope: !26)
!161 = !DILocation(line: 86, column: 1, scope: !26)
