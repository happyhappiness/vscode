; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [13 x i8] c"*vli_pos < 9\00", align 1
@.str.1 = private unnamed_addr constant [83 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_encoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_vli_encode = private unnamed_addr constant [90 x i8] c"lzma_ret lzma_vli_encode(lzma_vli, size_t *, uint8_t *restrict, size_t *restrict, size_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_vli_encode(i64 %vli, i64* %vli_pos, i8* noalias %out, i64* noalias %out_pos, i64 %out_size) #0 !dbg !24 {
entry:
  %retval = alloca i32, align 4
  %vli.addr = alloca i64, align 8
  %vli_pos.addr = alloca i64*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %vli_pos_internal = alloca i64, align 8
  store i64 %vli, i64* %vli.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %vli.addr, metadata !42, metadata !43), !dbg !44
  store i64* %vli_pos, i64** %vli_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %vli_pos.addr, metadata !45, metadata !43), !dbg !46
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !47, metadata !43), !dbg !48
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !49, metadata !43), !dbg !50
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !51, metadata !43), !dbg !52
  call void @llvm.dbg.declare(metadata i64* %vli_pos_internal, metadata !53, metadata !43), !dbg !54
  store i64 0, i64* %vli_pos_internal, align 8, !dbg !54
  %0 = load i64*, i64** %vli_pos.addr, align 8, !dbg !55
  %cmp = icmp eq i64* %0, null, !dbg !57
  br i1 %cmp, label %if.then, label %if.else, !dbg !58

if.then:                                          ; preds = %entry
  store i64* %vli_pos_internal, i64** %vli_pos.addr, align 8, !dbg !59
  %1 = load i64*, i64** %out_pos.addr, align 8, !dbg !61
  %2 = load i64, i64* %1, align 8, !dbg !63
  %3 = load i64, i64* %out_size.addr, align 8, !dbg !64
  %cmp1 = icmp uge i64 %2, %3, !dbg !65
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !66

if.then2:                                         ; preds = %if.then
  store i32 11, i32* %retval, align 4, !dbg !67
  br label %return, !dbg !67

if.end:                                           ; preds = %if.then
  br label %if.end6, !dbg !68

if.else:                                          ; preds = %entry
  %4 = load i64*, i64** %out_pos.addr, align 8, !dbg !69
  %5 = load i64, i64* %4, align 8, !dbg !72
  %6 = load i64, i64* %out_size.addr, align 8, !dbg !73
  %cmp3 = icmp uge i64 %5, %6, !dbg !74
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !75

if.then4:                                         ; preds = %if.else
  store i32 10, i32* %retval, align 4, !dbg !76
  br label %return, !dbg !76

if.end5:                                          ; preds = %if.else
  br label %if.end6

if.end6:                                          ; preds = %if.end5, %if.end
  %7 = load i64*, i64** %vli_pos.addr, align 8, !dbg !77
  %8 = load i64, i64* %7, align 8, !dbg !79
  %cmp7 = icmp uge i64 %8, 9, !dbg !80
  br i1 %cmp7, label %if.then9, label %lor.lhs.false, !dbg !81

lor.lhs.false:                                    ; preds = %if.end6
  %9 = load i64, i64* %vli.addr, align 8, !dbg !82
  %cmp8 = icmp ugt i64 %9, 9223372036854775807, !dbg !84
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !85

if.then9:                                         ; preds = %lor.lhs.false, %if.end6
  store i32 11, i32* %retval, align 4, !dbg !86
  br label %return, !dbg !86

if.end10:                                         ; preds = %lor.lhs.false
  %10 = load i64*, i64** %vli_pos.addr, align 8, !dbg !87
  %11 = load i64, i64* %10, align 8, !dbg !88
  %mul = mul i64 %11, 7, !dbg !89
  %12 = load i64, i64* %vli.addr, align 8, !dbg !90
  %shr = lshr i64 %12, %mul, !dbg !90
  store i64 %shr, i64* %vli.addr, align 8, !dbg !90
  br label %while.cond, !dbg !91

while.cond:                                       ; preds = %if.end22, %if.end10
  %13 = load i64, i64* %vli.addr, align 8, !dbg !92
  %cmp11 = icmp uge i64 %13, 128, !dbg !94
  br i1 %cmp11, label %while.body, label %while.end, !dbg !95

while.body:                                       ; preds = %while.cond
  %14 = load i64*, i64** %vli_pos.addr, align 8, !dbg !96
  %15 = load i64, i64* %14, align 8, !dbg !98
  %inc = add i64 %15, 1, !dbg !98
  store i64 %inc, i64* %14, align 8, !dbg !98
  %16 = load i64*, i64** %vli_pos.addr, align 8, !dbg !99
  %17 = load i64, i64* %16, align 8, !dbg !99
  %cmp12 = icmp ult i64 %17, 9, !dbg !99
  br i1 %cmp12, label %cond.true, label %cond.false, !dbg !99

cond.true:                                        ; preds = %while.body
  br label %cond.end, !dbg !100

cond.false:                                       ; preds = %while.body
  call void @__assert_fail(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([83 x i8], [83 x i8]* @.str.1, i32 0, i32 0), i32 51, i8* getelementptr inbounds ([90 x i8], [90 x i8]* @__PRETTY_FUNCTION__.lzma_vli_encode, i32 0, i32 0)) #3, !dbg !102
  unreachable, !dbg !102
                                                  ; No predecessors!
  br label %cond.end, !dbg !104

cond.end:                                         ; preds = %18, %cond.true
  %19 = load i64, i64* %vli.addr, align 8, !dbg !106
  %conv = trunc i64 %19 to i8, !dbg !107
  %conv13 = zext i8 %conv to i32, !dbg !107
  %or = or i32 %conv13, 128, !dbg !108
  %conv14 = trunc i32 %or to i8, !dbg !107
  %20 = load i64*, i64** %out_pos.addr, align 8, !dbg !109
  %21 = load i64, i64* %20, align 8, !dbg !110
  %22 = load i8*, i8** %out.addr, align 8, !dbg !111
  %arrayidx = getelementptr inbounds i8, i8* %22, i64 %21, !dbg !111
  store i8 %conv14, i8* %arrayidx, align 1, !dbg !112
  %23 = load i64, i64* %vli.addr, align 8, !dbg !113
  %shr15 = lshr i64 %23, 7, !dbg !113
  store i64 %shr15, i64* %vli.addr, align 8, !dbg !113
  %24 = load i64*, i64** %out_pos.addr, align 8, !dbg !114
  %25 = load i64, i64* %24, align 8, !dbg !116
  %inc16 = add i64 %25, 1, !dbg !116
  store i64 %inc16, i64* %24, align 8, !dbg !116
  %26 = load i64, i64* %out_size.addr, align 8, !dbg !117
  %cmp17 = icmp eq i64 %inc16, %26, !dbg !118
  br i1 %cmp17, label %if.then19, label %if.end22, !dbg !119

if.then19:                                        ; preds = %cond.end
  %27 = load i64*, i64** %vli_pos.addr, align 8, !dbg !120
  %cmp20 = icmp eq i64* %27, %vli_pos_internal, !dbg !121
  %cond = select i1 %cmp20, i32 11, i32 0, !dbg !120
  store i32 %cond, i32* %retval, align 4, !dbg !122
  br label %return, !dbg !122

if.end22:                                         ; preds = %cond.end
  br label %while.cond, !dbg !123

while.end:                                        ; preds = %while.cond
  %28 = load i64, i64* %vli.addr, align 8, !dbg !125
  %conv23 = trunc i64 %28 to i8, !dbg !126
  %29 = load i64*, i64** %out_pos.addr, align 8, !dbg !127
  %30 = load i64, i64* %29, align 8, !dbg !128
  %31 = load i8*, i8** %out.addr, align 8, !dbg !129
  %arrayidx24 = getelementptr inbounds i8, i8* %31, i64 %30, !dbg !129
  store i8 %conv23, i8* %arrayidx24, align 1, !dbg !130
  %32 = load i64*, i64** %out_pos.addr, align 8, !dbg !131
  %33 = load i64, i64* %32, align 8, !dbg !132
  %inc25 = add i64 %33, 1, !dbg !132
  store i64 %inc25, i64* %32, align 8, !dbg !132
  %34 = load i64*, i64** %vli_pos.addr, align 8, !dbg !133
  %35 = load i64, i64* %34, align 8, !dbg !134
  %inc26 = add i64 %35, 1, !dbg !134
  store i64 %inc26, i64* %34, align 8, !dbg !134
  %36 = load i64*, i64** %vli_pos.addr, align 8, !dbg !135
  %cmp27 = icmp eq i64* %36, %vli_pos_internal, !dbg !136
  %cond29 = select i1 %cmp27, i32 0, i32 1, !dbg !135
  store i32 %cond29, i32* %retval, align 4, !dbg !137
  br label %return, !dbg !137

return:                                           ; preds = %while.end, %if.then19, %if.then9, %if.then4, %if.then2
  %37 = load i32, i32* %retval, align 4, !dbg !138
  ret i32 %37, !dbg !138
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!39, !40}
!llvm.ident = !{!41}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !23)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/vli_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !21, line: 48, baseType: !22)
!21 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!22 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!23 = !{!24}
!24 = distinct !DISubprogram(name: "lzma_vli_encode", scope: !1, file: !1, line: 17, type: !25, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !38)
!25 = !DISubroutineType(types: !26)
!26 = !{!27, !28, !32, !35, !37, !33}
!27 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !29, line: 63, baseType: !30)
!29 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !21, line: 55, baseType: !31)
!31 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !34, line: 62, baseType: !31)
!34 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!35 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !36)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !32)
!38 = !{}
!39 = !{i32 2, !"Dwarf Version", i32 4}
!40 = !{i32 2, !"Debug Info Version", i32 3}
!41 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!42 = !DILocalVariable(name: "vli", arg: 1, scope: !24, file: !1, line: 17, type: !28)
!43 = !DIExpression()
!44 = !DILocation(line: 17, column: 26, scope: !24)
!45 = !DILocalVariable(name: "vli_pos", arg: 2, scope: !24, file: !1, line: 17, type: !32)
!46 = !DILocation(line: 17, column: 39, scope: !24)
!47 = !DILocalVariable(name: "out", arg: 3, scope: !24, file: !1, line: 18, type: !35)
!48 = !DILocation(line: 18, column: 26, scope: !24)
!49 = !DILocalVariable(name: "out_pos", arg: 4, scope: !24, file: !1, line: 18, type: !37)
!50 = !DILocation(line: 18, column: 53, scope: !24)
!51 = !DILocalVariable(name: "out_size", arg: 5, scope: !24, file: !1, line: 19, type: !33)
!52 = !DILocation(line: 19, column: 10, scope: !24)
!53 = !DILocalVariable(name: "vli_pos_internal", scope: !24, file: !1, line: 22, type: !33)
!54 = !DILocation(line: 22, column: 9, scope: !24)
!55 = !DILocation(line: 23, column: 6, scope: !56)
!56 = distinct !DILexicalBlock(scope: !24, file: !1, line: 23, column: 6)
!57 = !DILocation(line: 23, column: 14, scope: !56)
!58 = !DILocation(line: 23, column: 6, scope: !24)
!59 = !DILocation(line: 24, column: 11, scope: !60)
!60 = distinct !DILexicalBlock(scope: !56, file: !1, line: 23, column: 23)
!61 = !DILocation(line: 28, column: 8, scope: !62)
!62 = distinct !DILexicalBlock(scope: !60, file: !1, line: 28, column: 7)
!63 = !DILocation(line: 28, column: 7, scope: !62)
!64 = !DILocation(line: 28, column: 19, scope: !62)
!65 = !DILocation(line: 28, column: 16, scope: !62)
!66 = !DILocation(line: 28, column: 7, scope: !60)
!67 = !DILocation(line: 29, column: 4, scope: !62)
!68 = !DILocation(line: 30, column: 2, scope: !60)
!69 = !DILocation(line: 33, column: 8, scope: !70)
!70 = distinct !DILexicalBlock(scope: !71, file: !1, line: 33, column: 7)
!71 = distinct !DILexicalBlock(scope: !56, file: !1, line: 30, column: 9)
!72 = !DILocation(line: 33, column: 7, scope: !70)
!73 = !DILocation(line: 33, column: 19, scope: !70)
!74 = !DILocation(line: 33, column: 16, scope: !70)
!75 = !DILocation(line: 33, column: 7, scope: !71)
!76 = !DILocation(line: 34, column: 4, scope: !70)
!77 = !DILocation(line: 38, column: 7, scope: !78)
!78 = distinct !DILexicalBlock(scope: !24, file: !1, line: 38, column: 6)
!79 = !DILocation(line: 38, column: 6, scope: !78)
!80 = !DILocation(line: 38, column: 15, scope: !78)
!81 = !DILocation(line: 38, column: 37, scope: !78)
!82 = !DILocation(line: 38, column: 40, scope: !83)
!83 = !DILexicalBlockFile(scope: !78, file: !1, discriminator: 1)
!84 = !DILocation(line: 38, column: 44, scope: !83)
!85 = !DILocation(line: 38, column: 6, scope: !83)
!86 = !DILocation(line: 39, column: 3, scope: !78)
!87 = !DILocation(line: 43, column: 11, scope: !24)
!88 = !DILocation(line: 43, column: 10, scope: !24)
!89 = !DILocation(line: 43, column: 19, scope: !24)
!90 = !DILocation(line: 43, column: 6, scope: !24)
!91 = !DILocation(line: 46, column: 2, scope: !24)
!92 = !DILocation(line: 46, column: 9, scope: !93)
!93 = !DILexicalBlockFile(scope: !24, file: !1, discriminator: 1)
!94 = !DILocation(line: 46, column: 13, scope: !93)
!95 = !DILocation(line: 46, column: 2, scope: !93)
!96 = !DILocation(line: 50, column: 6, scope: !97)
!97 = distinct !DILexicalBlock(scope: !24, file: !1, line: 46, column: 22)
!98 = !DILocation(line: 50, column: 3, scope: !97)
!99 = !DILocation(line: 51, column: 3, scope: !97)
!100 = !DILocation(line: 51, column: 3, scope: !101)
!101 = !DILexicalBlockFile(scope: !97, file: !1, discriminator: 1)
!102 = !DILocation(line: 51, column: 3, scope: !103)
!103 = !DILexicalBlockFile(scope: !97, file: !1, discriminator: 2)
!104 = !DILocation(line: 51, column: 3, scope: !105)
!105 = !DILexicalBlockFile(scope: !97, file: !1, discriminator: 3)
!106 = !DILocation(line: 54, column: 29, scope: !97)
!107 = !DILocation(line: 54, column: 19, scope: !97)
!108 = !DILocation(line: 54, column: 34, scope: !97)
!109 = !DILocation(line: 54, column: 8, scope: !97)
!110 = !DILocation(line: 54, column: 7, scope: !97)
!111 = !DILocation(line: 54, column: 3, scope: !97)
!112 = !DILocation(line: 54, column: 17, scope: !97)
!113 = !DILocation(line: 55, column: 7, scope: !97)
!114 = !DILocation(line: 57, column: 10, scope: !115)
!115 = distinct !DILexicalBlock(scope: !97, file: !1, line: 57, column: 7)
!116 = !DILocation(line: 57, column: 7, scope: !115)
!117 = !DILocation(line: 57, column: 21, scope: !115)
!118 = !DILocation(line: 57, column: 18, scope: !115)
!119 = !DILocation(line: 57, column: 7, scope: !97)
!120 = !DILocation(line: 58, column: 11, scope: !115)
!121 = !DILocation(line: 58, column: 19, scope: !115)
!122 = !DILocation(line: 58, column: 4, scope: !115)
!123 = !DILocation(line: 46, column: 2, scope: !124)
!124 = !DILexicalBlockFile(scope: !24, file: !1, discriminator: 2)
!125 = !DILocation(line: 63, column: 28, scope: !24)
!126 = !DILocation(line: 63, column: 18, scope: !24)
!127 = !DILocation(line: 63, column: 7, scope: !24)
!128 = !DILocation(line: 63, column: 6, scope: !24)
!129 = !DILocation(line: 63, column: 2, scope: !24)
!130 = !DILocation(line: 63, column: 16, scope: !24)
!131 = !DILocation(line: 64, column: 5, scope: !24)
!132 = !DILocation(line: 64, column: 2, scope: !24)
!133 = !DILocation(line: 65, column: 5, scope: !24)
!134 = !DILocation(line: 65, column: 2, scope: !24)
!135 = !DILocation(line: 67, column: 9, scope: !24)
!136 = !DILocation(line: 67, column: 17, scope: !24)
!137 = !DILocation(line: 67, column: 2, scope: !24)
!138 = !DILocation(line: 69, column: 1, scope: !24)
