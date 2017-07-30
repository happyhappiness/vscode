; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_buffer_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_options_easy = type { [5 x %struct.lzma_filter], %struct.lzma_options_lzma }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_easy_buffer_encode(i32 %preset, i32 %check, %struct.lzma_allocator* %allocator, i8* %in, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !41 {
entry:
  %retval = alloca i32, align 4
  %preset.addr = alloca i32, align 4
  %check.addr = alloca i32, align 4
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %opt_easy = alloca %struct.lzma_options_easy, align 8
  store i32 %preset, i32* %preset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %preset.addr, metadata !76, metadata !77), !dbg !78
  store i32 %check, i32* %check.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %check.addr, metadata !79, metadata !77), !dbg !80
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !81, metadata !77), !dbg !82
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !83, metadata !77), !dbg !84
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !85, metadata !77), !dbg !86
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !87, metadata !77), !dbg !88
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !89, metadata !77), !dbg !90
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !91, metadata !77), !dbg !92
  call void @llvm.dbg.declare(metadata %struct.lzma_options_easy* %opt_easy, metadata !93, metadata !77), !dbg !142
  %0 = load i32, i32* %preset.addr, align 4, !dbg !143
  %call = call zeroext i1 @lzma_easy_preset(%struct.lzma_options_easy* %opt_easy, i32 %0), !dbg !145
  br i1 %call, label %if.then, label %if.end, !dbg !146

if.then:                                          ; preds = %entry
  store i32 8, i32* %retval, align 4, !dbg !147
  br label %return, !dbg !147

if.end:                                           ; preds = %entry
  %filters = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %opt_easy, i32 0, i32 0, !dbg !148
  %arraydecay = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i32 0, i32 0, !dbg !149
  %1 = load i32, i32* %check.addr, align 4, !dbg !150
  %2 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !151
  %3 = load i8*, i8** %in.addr, align 8, !dbg !152
  %4 = load i64, i64* %in_size.addr, align 8, !dbg !153
  %5 = load i8*, i8** %out.addr, align 8, !dbg !154
  %6 = load i64*, i64** %out_pos.addr, align 8, !dbg !155
  %7 = load i64, i64* %out_size.addr, align 8, !dbg !156
  %call1 = call i32 @lzma_stream_buffer_encode(%struct.lzma_filter* %arraydecay, i32 %1, %struct.lzma_allocator* %2, i8* %3, i64 %4, i8* %5, i64* %6, i64 %7) #4, !dbg !157
  store i32 %call1, i32* %retval, align 4, !dbg !158
  br label %return, !dbg !158

return:                                           ; preds = %if.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !159
  ret i32 %8, !dbg !159
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare zeroext i1 @lzma_easy_preset(%struct.lzma_options_easy*, i32) #2

; Function Attrs: nounwind
declare i32 @lzma_stream_buffer_encode(%struct.lzma_filter*, i32, %struct.lzma_allocator*, i8*, i64, i8*, i64*, i64) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!73, !74}
!llvm.ident = !{!75}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !40)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_buffer_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !25, !30, !37}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !19, line: 27, size: 32, align: 32, elements: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!20 = !{!21, !22, !23, !24}
!21 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!22 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!23 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!24 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !26, line: 138, size: 32, align: 32, elements: !27)
!26 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!27 = !{!28, !29}
!28 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!29 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!30 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !26, line: 58, size: 32, align: 32, elements: !31)
!31 = !{!32, !33, !34, !35, !36}
!32 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!33 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!34 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!35 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!36 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!37 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 44, size: 32, align: 32, elements: !38)
!38 = !{!39}
!39 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!40 = !{!41}
!41 = distinct !DISubprogram(name: "lzma_easy_buffer_encode", scope: !1, file: !1, line: 17, type: !42, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!42 = !DISubroutineType(types: !43)
!43 = !{!44, !45, !48, !49, !66, !58, !70, !71, !58}
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !46, line: 51, baseType: !47)
!46 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!47 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !19, line: 55, baseType: !18)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !51)
!51 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !52)
!52 = !{!53, !61, !65}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !51, file: !4, line: 376, baseType: !54, size: 64, align: 64)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!57, !57, !58, !58}
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !59, line: 62, baseType: !60)
!59 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!60 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !51, file: !4, line: 390, baseType: !62, size: 64, align: 64, offset: 64)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{null, !57, !57}
!65 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !51, file: !4, line: 401, baseType: !57, size: 64, align: 64, offset: 128)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !68)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !46, line: 48, baseType: !69)
!69 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!72 = !{}
!73 = !{i32 2, !"Dwarf Version", i32 4}
!74 = !{i32 2, !"Debug Info Version", i32 3}
!75 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!76 = !DILocalVariable(name: "preset", arg: 1, scope: !41, file: !1, line: 17, type: !45)
!77 = !DIExpression()
!78 = !DILocation(line: 17, column: 34, scope: !41)
!79 = !DILocalVariable(name: "check", arg: 2, scope: !41, file: !1, line: 17, type: !48)
!80 = !DILocation(line: 17, column: 53, scope: !41)
!81 = !DILocalVariable(name: "allocator", arg: 3, scope: !41, file: !1, line: 18, type: !49)
!82 = !DILocation(line: 18, column: 19, scope: !41)
!83 = !DILocalVariable(name: "in", arg: 4, scope: !41, file: !1, line: 18, type: !66)
!84 = !DILocation(line: 18, column: 45, scope: !41)
!85 = !DILocalVariable(name: "in_size", arg: 5, scope: !41, file: !1, line: 18, type: !58)
!86 = !DILocation(line: 18, column: 56, scope: !41)
!87 = !DILocalVariable(name: "out", arg: 6, scope: !41, file: !1, line: 19, type: !70)
!88 = !DILocation(line: 19, column: 12, scope: !41)
!89 = !DILocalVariable(name: "out_pos", arg: 7, scope: !41, file: !1, line: 19, type: !71)
!90 = !DILocation(line: 19, column: 25, scope: !41)
!91 = !DILocalVariable(name: "out_size", arg: 8, scope: !41, file: !1, line: 19, type: !58)
!92 = !DILocation(line: 19, column: 41, scope: !41)
!93 = !DILocalVariable(name: "opt_easy", scope: !41, file: !1, line: 21, type: !94)
!94 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_easy", file: !95, line: 27, baseType: !96)
!95 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_preset.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!96 = !DICompositeType(tag: DW_TAG_structure_type, file: !95, line: 16, size: 1536, align: 64, elements: !97)
!97 = !{!98, !111}
!98 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !96, file: !95, line: 19, baseType: !99, size: 640, align: 64)
!99 = !DICompositeType(tag: DW_TAG_array_type, baseType: !100, size: 640, align: 64, elements: !109)
!100 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !101, line: 65, baseType: !102)
!101 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!102 = !DICompositeType(tag: DW_TAG_structure_type, file: !101, line: 43, size: 128, align: 64, elements: !103)
!103 = !{!104, !108}
!104 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !102, file: !101, line: 54, baseType: !105, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !106, line: 63, baseType: !107)
!106 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!107 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !46, line: 55, baseType: !60)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !102, file: !101, line: 63, baseType: !57, size: 64, align: 64, offset: 64)
!109 = !{!110}
!110 = !DISubrange(count: 5)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "opt_lzma", scope: !96, file: !95, line: 22, baseType: !112, size: 896, align: 64, offset: 640)
!112 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !26, line: 399, baseType: !113)
!113 = !DICompositeType(tag: DW_TAG_structure_type, file: !26, line: 185, size: 896, align: 64, elements: !114)
!114 = !{!115, !116, !117, !118, !119, !120, !121, !123, !124, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !137, !138, !139, !140, !141}
!115 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !113, file: !26, line: 217, baseType: !45, size: 32, align: 32)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !113, file: !26, line: 240, baseType: !66, size: 64, align: 64, offset: 64)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !113, file: !26, line: 254, baseType: !45, size: 32, align: 32, offset: 128)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !113, file: !26, line: 281, baseType: !45, size: 32, align: 32, offset: 160)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !113, file: !26, line: 293, baseType: !45, size: 32, align: 32, offset: 192)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !113, file: !26, line: 316, baseType: !45, size: 32, align: 32, offset: 224)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !113, file: !26, line: 322, baseType: !122, size: 32, align: 32, offset: 256)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !26, line: 155, baseType: !25)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !113, file: !26, line: 342, baseType: !45, size: 32, align: 32, offset: 288)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !113, file: !26, line: 345, baseType: !125, size: 32, align: 32, offset: 320)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !26, line: 111, baseType: !30)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !113, file: !26, line: 375, baseType: !45, size: 32, align: 32, offset: 352)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !113, file: !26, line: 384, baseType: !45, size: 32, align: 32, offset: 384)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !113, file: !26, line: 385, baseType: !45, size: 32, align: 32, offset: 416)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !113, file: !26, line: 386, baseType: !45, size: 32, align: 32, offset: 448)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !113, file: !26, line: 387, baseType: !45, size: 32, align: 32, offset: 480)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !113, file: !26, line: 388, baseType: !45, size: 32, align: 32, offset: 512)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !113, file: !26, line: 389, baseType: !45, size: 32, align: 32, offset: 544)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !113, file: !26, line: 390, baseType: !45, size: 32, align: 32, offset: 576)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !113, file: !26, line: 391, baseType: !45, size: 32, align: 32, offset: 608)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !113, file: !26, line: 392, baseType: !136, size: 32, align: 32, offset: 640)
!136 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !4, line: 46, baseType: !37)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !113, file: !26, line: 393, baseType: !136, size: 32, align: 32, offset: 672)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !113, file: !26, line: 394, baseType: !136, size: 32, align: 32, offset: 704)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !113, file: !26, line: 395, baseType: !136, size: 32, align: 32, offset: 736)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !113, file: !26, line: 396, baseType: !57, size: 64, align: 64, offset: 768)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !113, file: !26, line: 397, baseType: !57, size: 64, align: 64, offset: 832)
!142 = !DILocation(line: 21, column: 20, scope: !41)
!143 = !DILocation(line: 22, column: 34, scope: !144)
!144 = distinct !DILexicalBlock(scope: !41, file: !1, line: 22, column: 6)
!145 = !DILocation(line: 22, column: 6, scope: !144)
!146 = !DILocation(line: 22, column: 6, scope: !41)
!147 = !DILocation(line: 23, column: 3, scope: !144)
!148 = !DILocation(line: 25, column: 44, scope: !41)
!149 = !DILocation(line: 25, column: 35, scope: !41)
!150 = !DILocation(line: 25, column: 53, scope: !41)
!151 = !DILocation(line: 26, column: 4, scope: !41)
!152 = !DILocation(line: 26, column: 15, scope: !41)
!153 = !DILocation(line: 26, column: 19, scope: !41)
!154 = !DILocation(line: 26, column: 28, scope: !41)
!155 = !DILocation(line: 26, column: 33, scope: !41)
!156 = !DILocation(line: 26, column: 42, scope: !41)
!157 = !DILocation(line: 25, column: 9, scope: !41)
!158 = !DILocation(line: 25, column: 2, scope: !41)
!159 = !DILocation(line: 27, column: 1, scope: !41)
