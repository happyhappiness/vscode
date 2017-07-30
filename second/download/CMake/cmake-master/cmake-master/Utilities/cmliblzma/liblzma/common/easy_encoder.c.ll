; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_stream = type { i8*, i64, i64, i8*, i64, i64, %struct.lzma_allocator*, %struct.lzma_internal_s*, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i32, i32 }
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_internal_s = type { %struct.lzma_next_coder_s, i32, i64, [4 x i8], i8 }
%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_options_easy = type { [5 x %struct.lzma_filter], %struct.lzma_options_lzma }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_easy_encoder(%struct.lzma_stream* %strm, i32 %preset, i32 %check) #0 !dbg !143 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.lzma_stream*, align 8
  %preset.addr = alloca i32, align 4
  %check.addr = alloca i32, align 4
  %opt_easy = alloca %struct.lzma_options_easy, align 8
  store %struct.lzma_stream* %strm, %struct.lzma_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_stream** %strm.addr, metadata !177, metadata !178), !dbg !179
  store i32 %preset, i32* %preset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %preset.addr, metadata !180, metadata !178), !dbg !181
  store i32 %check, i32* %check.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %check.addr, metadata !182, metadata !178), !dbg !183
  call void @llvm.dbg.declare(metadata %struct.lzma_options_easy* %opt_easy, metadata !184, metadata !178), !dbg !223
  %0 = load i32, i32* %preset.addr, align 4, !dbg !224
  %call = call zeroext i1 @lzma_easy_preset(%struct.lzma_options_easy* %opt_easy, i32 %0), !dbg !226
  br i1 %call, label %if.then, label %if.end, !dbg !227

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !228
  br label %return, !dbg !228

if.end:                                           ; preds = %entry
  %1 = load %struct.lzma_stream*, %struct.lzma_stream** %strm.addr, align 8, !dbg !229
  %filters = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %opt_easy, i32 0, i32 0, !dbg !230
  %arraydecay = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i32 0, i32 0, !dbg !231
  %2 = load i32, i32* %check.addr, align 4, !dbg !232
  %call1 = call i32 @lzma_stream_encoder(%struct.lzma_stream* %1, %struct.lzma_filter* %arraydecay, i32 %2) #4, !dbg !233
  store i32 %call1, i32* %retval, align 4, !dbg !234
  br label %return, !dbg !234

return:                                           ; preds = %if.end, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !235
  ret i32 %3, !dbg !235
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare zeroext i1 @lzma_easy_preset(%struct.lzma_options_easy*, i32) #2

; Function Attrs: nounwind
declare i32 @lzma_stream_encoder(%struct.lzma_stream*, %struct.lzma_filter*, i32) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!174, !175}
!llvm.ident = !{!176}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !142)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24, !31, !127, !130, !135}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23}
!20 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!21 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!22 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!23 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !25, line: 27, size: 32, align: 32, elements: !26)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !{!27, !28, !29, !30}
!27 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!28 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!29 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!30 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!31 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !33, file: !32, line: 182, size: 32, align: 32, elements: !120)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!33 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_internal_s", file: !32, line: 174, size: 704, align: 64, elements: !34)
!34 = !{!35, !112, !113, !114, !119}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !33, file: !32, line: 176, baseType: !36, size: 512, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !32, line: 75, baseType: !37)
!37 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !32, line: 119, size: 512, align: 64, elements: !38)
!38 = !{!39, !43, !49, !51, !83, !88, !95, !100}
!39 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !37, file: !32, line: 121, baseType: !40, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !32, line: 73, baseType: !42)
!42 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !32, line: 73, flags: DIFlagFwdDecl)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !37, file: !32, line: 125, baseType: !44, size: 64, align: 64, offset: 64)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !45, line: 63, baseType: !46)
!45 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !47, line: 55, baseType: !48)
!47 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!48 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !37, file: !32, line: 131, baseType: !50, size: 64, align: 64, offset: 128)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !47, line: 122, baseType: !48)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !37, file: !32, line: 134, baseType: !52, size: 64, align: 64, offset: 192)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !32, line: 89, baseType: !53)
!53 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !54, size: 64, align: 64)
!54 = !DISubroutineType(types: !55)
!55 = !{!56, !40, !57, !73, !78, !66, !80, !78, !66, !82}
!56 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !59)
!59 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !60)
!60 = !{!61, !68, !72}
!61 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !59, file: !4, line: 376, baseType: !62, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{!65, !65, !66, !66}
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !67, line: 62, baseType: !48)
!67 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!68 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !59, file: !4, line: 390, baseType: !69, size: 64, align: 64, offset: 64)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{null, !65, !65}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !59, file: !4, line: 401, baseType: !65, size: 64, align: 64, offset: 128)
!73 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !74)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !76)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !47, line: 48, baseType: !77)
!77 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!78 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !79)
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !81)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !37, file: !32, line: 139, baseType: !84, size: 64, align: 64, offset: 256)
!84 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !32, line: 97, baseType: !85)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{null, !40, !57}
!88 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !37, file: !32, line: 143, baseType: !89, size: 64, align: 64, offset: 320)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!92, !93}
!92 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !41)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !37, file: !32, line: 147, baseType: !96, size: 64, align: 64, offset: 384)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DISubroutineType(types: !98)
!98 = !{!56, !40, !99, !99, !46}
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !37, file: !32, line: 152, baseType: !101, size: 64, align: 64, offset: 448)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DISubroutineType(types: !103)
!103 = !{!56, !40, !57, !104, !104}
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !106)
!106 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !107, line: 65, baseType: !108)
!107 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!108 = !DICompositeType(tag: DW_TAG_structure_type, file: !107, line: 43, size: 128, align: 64, elements: !109)
!109 = !{!110, !111}
!110 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !108, file: !107, line: 54, baseType: !44, size: 64, align: 64)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !108, file: !107, line: 63, baseType: !65, size: 64, align: 64, offset: 64)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "sequence", scope: !33, file: !32, line: 189, baseType: !31, size: 32, align: 32, offset: 512)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !33, file: !32, line: 194, baseType: !66, size: 64, align: 64, offset: 576)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "supported_actions", scope: !33, file: !32, line: 197, baseType: !115, size: 32, align: 8, offset: 640)
!115 = !DICompositeType(tag: DW_TAG_array_type, baseType: !116, size: 32, align: 8, elements: !117)
!116 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!117 = !{!118}
!118 = !DISubrange(count: 4)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "allow_buf_error", scope: !33, file: !32, line: 201, baseType: !116, size: 8, align: 8, offset: 672)
!120 = !{!121, !122, !123, !124, !125, !126}
!121 = !DIEnumerator(name: "ISEQ_RUN", value: 0)
!122 = !DIEnumerator(name: "ISEQ_SYNC_FLUSH", value: 1)
!123 = !DIEnumerator(name: "ISEQ_FULL_FLUSH", value: 2)
!124 = !DIEnumerator(name: "ISEQ_FINISH", value: 3)
!125 = !DIEnumerator(name: "ISEQ_END", value: 4)
!126 = !DIEnumerator(name: "ISEQ_ERROR", value: 5)
!127 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !128)
!128 = !{!129}
!129 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!130 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !131, line: 138, size: 32, align: 32, elements: !132)
!131 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!132 = !{!133, !134}
!133 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!134 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!135 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !131, line: 58, size: 32, align: 32, elements: !136)
!136 = !{!137, !138, !139, !140, !141}
!137 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!138 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!139 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!140 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!141 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!142 = !{!143}
!143 = distinct !DISubprogram(name: "lzma_easy_encoder", scope: !1, file: !1, line: 18, type: !144, isLocal: false, isDefinition: true, scopeLine: 19, flags: DIFlagPrototyped, isOptimized: false, variables: !173)
!144 = !DISubroutineType(types: !145)
!145 = !{!56, !146, !171, !92}
!146 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !147, size: 64, align: 64)
!147 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_stream", file: !4, line: 490, baseType: !148)
!148 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 453, size: 1088, align: 64, elements: !149)
!149 = !{!150, !151, !152, !153, !154, !155, !156, !157, !160, !161, !162, !163, !164, !165, !166, !167, !168, !170}
!150 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !148, file: !4, line: 454, baseType: !74, size: 64, align: 64)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !148, file: !4, line: 455, baseType: !66, size: 64, align: 64, offset: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !148, file: !4, line: 456, baseType: !46, size: 64, align: 64, offset: 128)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !148, file: !4, line: 458, baseType: !81, size: 64, align: 64, offset: 192)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !148, file: !4, line: 459, baseType: !66, size: 64, align: 64, offset: 256)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !148, file: !4, line: 460, baseType: !46, size: 64, align: 64, offset: 320)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "allocator", scope: !148, file: !4, line: 468, baseType: !57, size: 64, align: 64, offset: 384)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "internal", scope: !148, file: !4, line: 471, baseType: !158, size: 64, align: 64, offset: 448)
!158 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !159, size: 64, align: 64)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_internal", file: !4, line: 411, baseType: !33)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !148, file: !4, line: 479, baseType: !65, size: 64, align: 64, offset: 512)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !148, file: !4, line: 480, baseType: !65, size: 64, align: 64, offset: 576)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr3", scope: !148, file: !4, line: 481, baseType: !65, size: 64, align: 64, offset: 640)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr4", scope: !148, file: !4, line: 482, baseType: !65, size: 64, align: 64, offset: 704)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !148, file: !4, line: 483, baseType: !46, size: 64, align: 64, offset: 768)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !148, file: !4, line: 484, baseType: !46, size: 64, align: 64, offset: 832)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !148, file: !4, line: 485, baseType: !66, size: 64, align: 64, offset: 896)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !148, file: !4, line: 486, baseType: !66, size: 64, align: 64, offset: 960)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !148, file: !4, line: 487, baseType: !169, size: 32, align: 32, offset: 1024)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !127)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !148, file: !4, line: 488, baseType: !169, size: 32, align: 32, offset: 1056)
!171 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !47, line: 51, baseType: !172)
!172 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!173 = !{}
!174 = !{i32 2, !"Dwarf Version", i32 4}
!175 = !{i32 2, !"Debug Info Version", i32 3}
!176 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!177 = !DILocalVariable(name: "strm", arg: 1, scope: !143, file: !1, line: 18, type: !146)
!178 = !DIExpression()
!179 = !DILocation(line: 18, column: 32, scope: !143)
!180 = !DILocalVariable(name: "preset", arg: 2, scope: !143, file: !1, line: 18, type: !171)
!181 = !DILocation(line: 18, column: 47, scope: !143)
!182 = !DILocalVariable(name: "check", arg: 3, scope: !143, file: !1, line: 18, type: !92)
!183 = !DILocation(line: 18, column: 66, scope: !143)
!184 = !DILocalVariable(name: "opt_easy", scope: !143, file: !1, line: 20, type: !185)
!185 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_easy", file: !186, line: 27, baseType: !187)
!186 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_preset.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!187 = !DICompositeType(tag: DW_TAG_structure_type, file: !186, line: 16, size: 1536, align: 64, elements: !188)
!188 = !{!189, !193}
!189 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !187, file: !186, line: 19, baseType: !190, size: 640, align: 64)
!190 = !DICompositeType(tag: DW_TAG_array_type, baseType: !106, size: 640, align: 64, elements: !191)
!191 = !{!192}
!192 = !DISubrange(count: 5)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "opt_lzma", scope: !187, file: !186, line: 22, baseType: !194, size: 896, align: 64, offset: 640)
!194 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !131, line: 399, baseType: !195)
!195 = !DICompositeType(tag: DW_TAG_structure_type, file: !131, line: 185, size: 896, align: 64, elements: !196)
!196 = !{!197, !198, !199, !200, !201, !202, !203, !205, !206, !208, !209, !210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220, !221, !222}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !195, file: !131, line: 217, baseType: !171, size: 32, align: 32)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !195, file: !131, line: 240, baseType: !74, size: 64, align: 64, offset: 64)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !195, file: !131, line: 254, baseType: !171, size: 32, align: 32, offset: 128)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !195, file: !131, line: 281, baseType: !171, size: 32, align: 32, offset: 160)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !195, file: !131, line: 293, baseType: !171, size: 32, align: 32, offset: 192)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !195, file: !131, line: 316, baseType: !171, size: 32, align: 32, offset: 224)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !195, file: !131, line: 322, baseType: !204, size: 32, align: 32, offset: 256)
!204 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !131, line: 155, baseType: !130)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !195, file: !131, line: 342, baseType: !171, size: 32, align: 32, offset: 288)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !195, file: !131, line: 345, baseType: !207, size: 32, align: 32, offset: 320)
!207 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !131, line: 111, baseType: !135)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !195, file: !131, line: 375, baseType: !171, size: 32, align: 32, offset: 352)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !195, file: !131, line: 384, baseType: !171, size: 32, align: 32, offset: 384)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !195, file: !131, line: 385, baseType: !171, size: 32, align: 32, offset: 416)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !195, file: !131, line: 386, baseType: !171, size: 32, align: 32, offset: 448)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !195, file: !131, line: 387, baseType: !171, size: 32, align: 32, offset: 480)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !195, file: !131, line: 388, baseType: !171, size: 32, align: 32, offset: 512)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !195, file: !131, line: 389, baseType: !171, size: 32, align: 32, offset: 544)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !195, file: !131, line: 390, baseType: !171, size: 32, align: 32, offset: 576)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !195, file: !131, line: 391, baseType: !171, size: 32, align: 32, offset: 608)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !195, file: !131, line: 392, baseType: !169, size: 32, align: 32, offset: 640)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !195, file: !131, line: 393, baseType: !169, size: 32, align: 32, offset: 672)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !195, file: !131, line: 394, baseType: !169, size: 32, align: 32, offset: 704)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !195, file: !131, line: 395, baseType: !169, size: 32, align: 32, offset: 736)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !195, file: !131, line: 396, baseType: !65, size: 64, align: 64, offset: 768)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !195, file: !131, line: 397, baseType: !65, size: 64, align: 64, offset: 832)
!223 = !DILocation(line: 20, column: 20, scope: !143)
!224 = !DILocation(line: 21, column: 34, scope: !225)
!225 = distinct !DILexicalBlock(scope: !143, file: !1, line: 21, column: 6)
!226 = !DILocation(line: 21, column: 6, scope: !225)
!227 = !DILocation(line: 21, column: 6, scope: !143)
!228 = !DILocation(line: 22, column: 3, scope: !225)
!229 = !DILocation(line: 24, column: 29, scope: !143)
!230 = !DILocation(line: 24, column: 44, scope: !143)
!231 = !DILocation(line: 24, column: 35, scope: !143)
!232 = !DILocation(line: 24, column: 53, scope: !143)
!233 = !DILocation(line: 24, column: 9, scope: !143)
!234 = !DILocation(line: 24, column: 2, scope: !143)
!235 = !DILocation(line: 25, column: 1, scope: !143)
