; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_encoder_memusage.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_options_easy = type { [5 x %struct.lzma_filter], %struct.lzma_options_lzma }
%struct.lzma_filter = type { i64, i8* }
%struct.lzma_options_lzma = type { i32, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i8*, i8* }

; Function Attrs: nounwind readonly uwtable
define i64 @lzma_easy_encoder_memusage(i32 %preset) #0 !dbg !20 {
entry:
  %retval = alloca i64, align 8
  %preset.addr = alloca i32, align 4
  %opt_easy = alloca %struct.lzma_options_easy, align 8
  store i32 %preset, i32* %preset.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %preset.addr, metadata !32, metadata !33), !dbg !34
  call void @llvm.dbg.declare(metadata %struct.lzma_options_easy* %opt_easy, metadata !35, metadata !33), !dbg !88
  %0 = load i32, i32* %preset.addr, align 4, !dbg !89
  %call = call zeroext i1 @lzma_easy_preset(%struct.lzma_options_easy* %opt_easy, i32 %0), !dbg !91
  br i1 %call, label %if.then, label %if.end, !dbg !92

if.then:                                          ; preds = %entry
  store i64 4294967295, i64* %retval, align 8, !dbg !93
  br label %return, !dbg !93

if.end:                                           ; preds = %entry
  %filters = getelementptr inbounds %struct.lzma_options_easy, %struct.lzma_options_easy* %opt_easy, i32 0, i32 0, !dbg !94
  %arraydecay = getelementptr inbounds [5 x %struct.lzma_filter], [5 x %struct.lzma_filter]* %filters, i32 0, i32 0, !dbg !95
  %call1 = call i64 @lzma_raw_encoder_memusage(%struct.lzma_filter* %arraydecay) #4, !dbg !96
  store i64 %call1, i64* %retval, align 8, !dbg !97
  br label %return, !dbg !97

return:                                           ; preds = %if.end, %if.then
  %1 = load i64, i64* %retval, align 8, !dbg !98
  ret i64 %1, !dbg !98
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare zeroext i1 @lzma_easy_preset(%struct.lzma_options_easy*, i32) #2

; Function Attrs: nounwind readonly
declare i64 @lzma_raw_encoder_memusage(%struct.lzma_filter*) #3

attributes #0 = { nounwind readonly uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!29, !30}
!llvm.ident = !{!31}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !19)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_encoder_memusage.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !8, !15}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 138, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/lzma.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7}
!6 = !DIEnumerator(name: "LZMA_MODE_FAST", value: 1)
!7 = !DIEnumerator(name: "LZMA_MODE_NORMAL", value: 2)
!8 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 58, size: 32, align: 32, elements: !9)
!9 = !{!10, !11, !12, !13, !14}
!10 = !DIEnumerator(name: "LZMA_MF_HC3", value: 3)
!11 = !DIEnumerator(name: "LZMA_MF_HC4", value: 4)
!12 = !DIEnumerator(name: "LZMA_MF_BT2", value: 18)
!13 = !DIEnumerator(name: "LZMA_MF_BT3", value: 19)
!14 = !DIEnumerator(name: "LZMA_MF_BT4", value: 20)
!15 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 44, size: 32, align: 32, elements: !17)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!17 = !{!18}
!18 = !DIEnumerator(name: "LZMA_RESERVED_ENUM", value: 0)
!19 = !{!20}
!20 = distinct !DISubprogram(name: "lzma_easy_encoder_memusage", scope: !1, file: !1, line: 17, type: !21, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !28)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !26}
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !24, line: 55, baseType: !25)
!24 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!25 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!26 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !24, line: 51, baseType: !27)
!27 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!28 = !{}
!29 = !{i32 2, !"Dwarf Version", i32 4}
!30 = !{i32 2, !"Debug Info Version", i32 3}
!31 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!32 = !DILocalVariable(name: "preset", arg: 1, scope: !20, file: !1, line: 17, type: !26)
!33 = !DIExpression()
!34 = !DILocation(line: 17, column: 37, scope: !20)
!35 = !DILocalVariable(name: "opt_easy", scope: !20, file: !1, line: 19, type: !36)
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_easy", file: !37, line: 27, baseType: !38)
!37 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/easy_preset.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!38 = !DICompositeType(tag: DW_TAG_structure_type, file: !37, line: 16, size: 1536, align: 64, elements: !39)
!39 = !{!40, !53}
!40 = !DIDerivedType(tag: DW_TAG_member, name: "filters", scope: !38, file: !37, line: 19, baseType: !41, size: 640, align: 64)
!41 = !DICompositeType(tag: DW_TAG_array_type, baseType: !42, size: 640, align: 64, elements: !51)
!42 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !43, line: 65, baseType: !44)
!43 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!44 = !DICompositeType(tag: DW_TAG_structure_type, file: !43, line: 43, size: 128, align: 64, elements: !45)
!45 = !{!46, !49}
!46 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !44, file: !43, line: 54, baseType: !47, size: 64, align: 64)
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !48, line: 63, baseType: !23)
!48 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!49 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !44, file: !43, line: 63, baseType: !50, size: 64, align: 64, offset: 64)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!51 = !{!52}
!52 = !DISubrange(count: 5)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "opt_lzma", scope: !38, file: !37, line: 22, baseType: !54, size: 896, align: 64, offset: 640)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_options_lzma", file: !4, line: 399, baseType: !55)
!55 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 185, size: 896, align: 64, elements: !56)
!56 = !{!57, !58, !63, !64, !65, !66, !67, !69, !70, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !83, !84, !85, !86, !87}
!57 = !DIDerivedType(tag: DW_TAG_member, name: "dict_size", scope: !55, file: !4, line: 217, baseType: !26, size: 32, align: 32)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict", scope: !55, file: !4, line: 240, baseType: !59, size: 64, align: 64, offset: 64)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !61)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !24, line: 48, baseType: !62)
!62 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "preset_dict_size", scope: !55, file: !4, line: 254, baseType: !26, size: 32, align: 32, offset: 128)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "lc", scope: !55, file: !4, line: 281, baseType: !26, size: 32, align: 32, offset: 160)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "lp", scope: !55, file: !4, line: 293, baseType: !26, size: 32, align: 32, offset: 192)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "pb", scope: !55, file: !4, line: 316, baseType: !26, size: 32, align: 32, offset: 224)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !55, file: !4, line: 322, baseType: !68, size: 32, align: 32, offset: 256)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_mode", file: !4, line: 155, baseType: !3)
!69 = !DIDerivedType(tag: DW_TAG_member, name: "nice_len", scope: !55, file: !4, line: 342, baseType: !26, size: 32, align: 32, offset: 288)
!70 = !DIDerivedType(tag: DW_TAG_member, name: "mf", scope: !55, file: !4, line: 345, baseType: !71, size: 32, align: 32, offset: 320)
!71 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_match_finder", file: !4, line: 111, baseType: !8)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "depth", scope: !55, file: !4, line: 375, baseType: !26, size: 32, align: 32, offset: 352)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int1", scope: !55, file: !4, line: 384, baseType: !26, size: 32, align: 32, offset: 384)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int2", scope: !55, file: !4, line: 385, baseType: !26, size: 32, align: 32, offset: 416)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int3", scope: !55, file: !4, line: 386, baseType: !26, size: 32, align: 32, offset: 448)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int4", scope: !55, file: !4, line: 387, baseType: !26, size: 32, align: 32, offset: 480)
!77 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int5", scope: !55, file: !4, line: 388, baseType: !26, size: 32, align: 32, offset: 512)
!78 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int6", scope: !55, file: !4, line: 389, baseType: !26, size: 32, align: 32, offset: 544)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int7", scope: !55, file: !4, line: 390, baseType: !26, size: 32, align: 32, offset: 576)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_int8", scope: !55, file: !4, line: 391, baseType: !26, size: 32, align: 32, offset: 608)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum1", scope: !55, file: !4, line: 392, baseType: !82, size: 32, align: 32, offset: 640)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_reserved_enum", file: !16, line: 46, baseType: !15)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum2", scope: !55, file: !4, line: 393, baseType: !82, size: 32, align: 32, offset: 672)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum3", scope: !55, file: !4, line: 394, baseType: !82, size: 32, align: 32, offset: 704)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_enum4", scope: !55, file: !4, line: 395, baseType: !82, size: 32, align: 32, offset: 736)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr1", scope: !55, file: !4, line: 396, baseType: !50, size: 64, align: 64, offset: 768)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "reserved_ptr2", scope: !55, file: !4, line: 397, baseType: !50, size: 64, align: 64, offset: 832)
!88 = !DILocation(line: 19, column: 20, scope: !20)
!89 = !DILocation(line: 20, column: 34, scope: !90)
!90 = distinct !DILexicalBlock(scope: !20, file: !1, line: 20, column: 6)
!91 = !DILocation(line: 20, column: 6, scope: !90)
!92 = !DILocation(line: 20, column: 6, scope: !20)
!93 = !DILocation(line: 21, column: 3, scope: !90)
!94 = !DILocation(line: 23, column: 44, scope: !20)
!95 = !DILocation(line: 23, column: 35, scope: !20)
!96 = !DILocation(line: 23, column: 9, scope: !20)
!97 = !DILocation(line: 23, column: 2, scope: !20)
!98 = !DILocation(line: 24, column: 1, scope: !20)
