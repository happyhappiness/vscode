; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_flags_decoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_filter = type { i64, i8* }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_filter_flags_decode(%struct.lzma_filter* %filter, %struct.lzma_allocator* %allocator, i8* %in, i64* %in_pos, i64 %in_size) #0 !dbg !21 {
entry:
  %retval = alloca i32, align 4
  %filter.addr = alloca %struct.lzma_filter*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_pos.addr = alloca i64*, align 8
  %in_size.addr = alloca i64, align 8
  %props_size = alloca i64, align 8
  %ret = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %ret_6 = alloca i32, align 4
  store %struct.lzma_filter* %filter, %struct.lzma_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filter.addr, metadata !61, metadata !62), !dbg !63
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !64, metadata !62), !dbg !65
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !66, metadata !62), !dbg !67
  store i64* %in_pos, i64** %in_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %in_pos.addr, metadata !68, metadata !62), !dbg !69
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !70, metadata !62), !dbg !71
  call void @llvm.dbg.declare(metadata i64* %props_size, metadata !72, metadata !62), !dbg !73
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !74, metadata !62), !dbg !75
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !76
  %options = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i32 0, i32 1, !dbg !77
  store i8* null, i8** %options, align 8, !dbg !78
  br label %do.body, !dbg !79

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !80, metadata !62), !dbg !83
  %1 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !84
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %1, i32 0, i32 0, !dbg !84
  %2 = load i8*, i8** %in.addr, align 8, !dbg !84
  %3 = load i64*, i64** %in_pos.addr, align 8, !dbg !84
  %4 = load i64, i64* %in_size.addr, align 8, !dbg !84
  %call = call i32 @lzma_vli_decode(i64* %id, i64* null, i8* %2, i64* %3, i64 %4) #3, !dbg !84
  store i32 %call, i32* %ret_, align 4, !dbg !84
  %5 = load i32, i32* %ret_, align 4, !dbg !84
  %cmp = icmp ne i32 %5, 0, !dbg !84
  br i1 %cmp, label %if.then, label %if.end, !dbg !84

if.then:                                          ; preds = %do.body
  %6 = load i32, i32* %ret_, align 4, !dbg !86
  store i32 %6, i32* %retval, align 4, !dbg !86
  br label %return, !dbg !86

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !89

do.end:                                           ; preds = %if.end
  %7 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !91
  %id1 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %7, i32 0, i32 0, !dbg !93
  %8 = load i64, i64* %id1, align 8, !dbg !93
  %cmp2 = icmp uge i64 %8, 4611686018427387904, !dbg !94
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !95

if.then3:                                         ; preds = %do.end
  store i32 9, i32* %retval, align 4, !dbg !96
  br label %return, !dbg !96

if.end4:                                          ; preds = %do.end
  br label %do.body5, !dbg !97

do.body5:                                         ; preds = %if.end4
  call void @llvm.dbg.declare(metadata i32* %ret_6, metadata !98, metadata !62), !dbg !100
  %9 = load i8*, i8** %in.addr, align 8, !dbg !101
  %10 = load i64*, i64** %in_pos.addr, align 8, !dbg !101
  %11 = load i64, i64* %in_size.addr, align 8, !dbg !101
  %call7 = call i32 @lzma_vli_decode(i64* %props_size, i64* null, i8* %9, i64* %10, i64 %11) #3, !dbg !101
  store i32 %call7, i32* %ret_6, align 4, !dbg !101
  %12 = load i32, i32* %ret_6, align 4, !dbg !101
  %cmp8 = icmp ne i32 %12, 0, !dbg !101
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !101

if.then9:                                         ; preds = %do.body5
  %13 = load i32, i32* %ret_6, align 4, !dbg !103
  store i32 %13, i32* %retval, align 4, !dbg !103
  br label %return, !dbg !103

if.end10:                                         ; preds = %do.body5
  br label %do.end11, !dbg !106

do.end11:                                         ; preds = %if.end10
  %14 = load i64, i64* %in_size.addr, align 8, !dbg !108
  %15 = load i64*, i64** %in_pos.addr, align 8, !dbg !110
  %16 = load i64, i64* %15, align 8, !dbg !111
  %sub = sub i64 %14, %16, !dbg !112
  %17 = load i64, i64* %props_size, align 8, !dbg !113
  %cmp12 = icmp ult i64 %sub, %17, !dbg !114
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !115

if.then13:                                        ; preds = %do.end11
  store i32 9, i32* %retval, align 4, !dbg !116
  br label %return, !dbg !116

if.end14:                                         ; preds = %do.end11
  %18 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !117
  %19 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !118
  %20 = load i8*, i8** %in.addr, align 8, !dbg !119
  %21 = load i64*, i64** %in_pos.addr, align 8, !dbg !120
  %22 = load i64, i64* %21, align 8, !dbg !121
  %add.ptr = getelementptr inbounds i8, i8* %20, i64 %22, !dbg !122
  %23 = load i64, i64* %props_size, align 8, !dbg !123
  %call15 = call i32 @lzma_properties_decode(%struct.lzma_filter* %18, %struct.lzma_allocator* %19, i8* %add.ptr, i64 %23) #3, !dbg !124
  store i32 %call15, i32* %ret, align 4, !dbg !125
  %24 = load i64, i64* %props_size, align 8, !dbg !126
  %25 = load i64*, i64** %in_pos.addr, align 8, !dbg !127
  %26 = load i64, i64* %25, align 8, !dbg !128
  %add = add i64 %26, %24, !dbg !128
  store i64 %add, i64* %25, align 8, !dbg !128
  %27 = load i32, i32* %ret, align 4, !dbg !129
  store i32 %27, i32* %retval, align 4, !dbg !130
  br label %return, !dbg !130

return:                                           ; preds = %if.end14, %if.then13, %if.then9, %if.then3, %if.then
  %28 = load i32, i32* %retval, align 4, !dbg !131
  ret i32 %28, !dbg !131
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i32 @lzma_vli_decode(i64*, i64*, i8*, i64*, i64) #2

; Function Attrs: nounwind
declare i32 @lzma_properties_decode(%struct.lzma_filter*, %struct.lzma_allocator*, i8*, i64) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!58, !59}
!llvm.ident = !{!60}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !20)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_flags_decoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!18 = !{!19}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!20 = !{!21}
!21 = distinct !DISubprogram(name: "lzma_filter_flags_decode", scope: !1, file: !1, line: 17, type: !22, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !57)
!22 = !DISubroutineType(types: !23)
!23 = !{!24, !25, !37, !52, !56, !45}
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !27, line: 65, baseType: !28)
!27 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!28 = !DICompositeType(tag: DW_TAG_structure_type, file: !27, line: 43, size: 128, align: 64, elements: !29)
!29 = !{!30, !36}
!30 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !28, file: !27, line: 54, baseType: !31, size: 64, align: 64)
!31 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !32, line: 63, baseType: !33)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !34, line: 55, baseType: !35)
!34 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!35 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!36 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !28, file: !27, line: 63, baseType: !19, size: 64, align: 64, offset: 64)
!37 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !38, size: 64, align: 64)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !39)
!39 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !40)
!40 = !{!41, !47, !51}
!41 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !39, file: !4, line: 376, baseType: !42, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DISubroutineType(types: !44)
!44 = !{!19, !19, !45, !45}
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !35)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!47 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !39, file: !4, line: 390, baseType: !48, size: 64, align: 64, offset: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DISubroutineType(types: !50)
!50 = !{null, !19, !19}
!51 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !39, file: !4, line: 401, baseType: !19, size: 64, align: 64, offset: 128)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !54)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !34, line: 48, baseType: !55)
!55 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!57 = !{}
!58 = !{i32 2, !"Dwarf Version", i32 4}
!59 = !{i32 2, !"Debug Info Version", i32 3}
!60 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!61 = !DILocalVariable(name: "filter", arg: 1, scope: !21, file: !1, line: 18, type: !25)
!62 = !DIExpression()
!63 = !DILocation(line: 18, column: 16, scope: !21)
!64 = !DILocalVariable(name: "allocator", arg: 2, scope: !21, file: !1, line: 18, type: !37)
!65 = !DILocation(line: 18, column: 40, scope: !21)
!66 = !DILocalVariable(name: "in", arg: 3, scope: !21, file: !1, line: 19, type: !52)
!67 = !DILocation(line: 19, column: 18, scope: !21)
!68 = !DILocalVariable(name: "in_pos", arg: 4, scope: !21, file: !1, line: 19, type: !56)
!69 = !DILocation(line: 19, column: 30, scope: !21)
!70 = !DILocalVariable(name: "in_size", arg: 5, scope: !21, file: !1, line: 19, type: !45)
!71 = !DILocation(line: 19, column: 45, scope: !21)
!72 = !DILocalVariable(name: "props_size", scope: !21, file: !1, line: 21, type: !31)
!73 = !DILocation(line: 21, column: 11, scope: !21)
!74 = !DILocalVariable(name: "ret", scope: !21, file: !1, line: 22, type: !24)
!75 = !DILocation(line: 22, column: 11, scope: !21)
!76 = !DILocation(line: 25, column: 2, scope: !21)
!77 = !DILocation(line: 25, column: 10, scope: !21)
!78 = !DILocation(line: 25, column: 18, scope: !21)
!79 = !DILocation(line: 28, column: 2, scope: !21)
!80 = !DILocalVariable(name: "ret_", scope: !81, file: !1, line: 28, type: !82)
!81 = distinct !DILexicalBlock(scope: !21, file: !1, line: 28, column: 2)
!82 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !24)
!83 = !DILocation(line: 28, column: 2, scope: !81)
!84 = !DILocation(line: 28, column: 2, scope: !85)
!85 = !DILexicalBlockFile(scope: !81, file: !1, discriminator: 1)
!86 = !DILocation(line: 28, column: 2, scope: !87)
!87 = !DILexicalBlockFile(scope: !88, file: !1, discriminator: 2)
!88 = distinct !DILexicalBlock(scope: !81, file: !1, line: 28, column: 2)
!89 = !DILocation(line: 28, column: 2, scope: !90)
!90 = !DILexicalBlockFile(scope: !81, file: !1, discriminator: 3)
!91 = !DILocation(line: 31, column: 6, scope: !92)
!92 = distinct !DILexicalBlock(scope: !21, file: !1, line: 31, column: 6)
!93 = !DILocation(line: 31, column: 14, scope: !92)
!94 = !DILocation(line: 31, column: 17, scope: !92)
!95 = !DILocation(line: 31, column: 6, scope: !21)
!96 = !DILocation(line: 32, column: 3, scope: !92)
!97 = !DILocation(line: 35, column: 2, scope: !21)
!98 = !DILocalVariable(name: "ret_", scope: !99, file: !1, line: 35, type: !82)
!99 = distinct !DILexicalBlock(scope: !21, file: !1, line: 35, column: 2)
!100 = !DILocation(line: 35, column: 2, scope: !99)
!101 = !DILocation(line: 35, column: 2, scope: !102)
!102 = !DILexicalBlockFile(scope: !99, file: !1, discriminator: 1)
!103 = !DILocation(line: 35, column: 2, scope: !104)
!104 = !DILexicalBlockFile(scope: !105, file: !1, discriminator: 2)
!105 = distinct !DILexicalBlock(scope: !99, file: !1, line: 35, column: 2)
!106 = !DILocation(line: 35, column: 2, scope: !107)
!107 = !DILexicalBlockFile(scope: !99, file: !1, discriminator: 3)
!108 = !DILocation(line: 39, column: 6, scope: !109)
!109 = distinct !DILexicalBlock(scope: !21, file: !1, line: 39, column: 6)
!110 = !DILocation(line: 39, column: 17, scope: !109)
!111 = !DILocation(line: 39, column: 16, scope: !109)
!112 = !DILocation(line: 39, column: 14, scope: !109)
!113 = !DILocation(line: 39, column: 26, scope: !109)
!114 = !DILocation(line: 39, column: 24, scope: !109)
!115 = !DILocation(line: 39, column: 6, scope: !21)
!116 = !DILocation(line: 40, column: 3, scope: !109)
!117 = !DILocation(line: 43, column: 4, scope: !21)
!118 = !DILocation(line: 43, column: 12, scope: !21)
!119 = !DILocation(line: 43, column: 23, scope: !21)
!120 = !DILocation(line: 43, column: 29, scope: !21)
!121 = !DILocation(line: 43, column: 28, scope: !21)
!122 = !DILocation(line: 43, column: 26, scope: !21)
!123 = !DILocation(line: 43, column: 37, scope: !21)
!124 = !DILocation(line: 42, column: 8, scope: !21)
!125 = !DILocation(line: 42, column: 6, scope: !21)
!126 = !DILocation(line: 45, column: 13, scope: !21)
!127 = !DILocation(line: 45, column: 3, scope: !21)
!128 = !DILocation(line: 45, column: 10, scope: !21)
!129 = !DILocation(line: 47, column: 9, scope: !21)
!130 = !DILocation(line: 47, column: 2, scope: !21)
!131 = !DILocation(line: 48, column: 1, scope: !21)
