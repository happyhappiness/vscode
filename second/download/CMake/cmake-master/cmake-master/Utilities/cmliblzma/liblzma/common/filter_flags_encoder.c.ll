; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_flags_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_filter = type { i64, i8* }

; Function Attrs: nounwind uwtable
define i32 @lzma_filter_flags_size(i32* %size, %struct.lzma_filter* %filter) #0 !dbg !19 {
entry:
  %retval = alloca i32, align 4
  %size.addr = alloca i32*, align 8
  %filter.addr = alloca %struct.lzma_filter*, align 8
  %ret_ = alloca i32, align 4
  store i32* %size, i32** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %size.addr, metadata !53, metadata !54), !dbg !55
  store %struct.lzma_filter* %filter, %struct.lzma_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filter.addr, metadata !56, metadata !54), !dbg !57
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !58
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i32 0, i32 0, !dbg !60
  %1 = load i64, i64* %id, align 8, !dbg !60
  %cmp = icmp uge i64 %1, 4611686018427387904, !dbg !61
  br i1 %cmp, label %if.then, label %if.end, !dbg !62

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !63
  br label %return, !dbg !63

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !64

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !65, metadata !54), !dbg !68
  %2 = load i32*, i32** %size.addr, align 8, !dbg !69
  %3 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !69
  %call = call i32 @lzma_properties_size(i32* %2, %struct.lzma_filter* %3) #4, !dbg !69
  store i32 %call, i32* %ret_, align 4, !dbg !69
  %4 = load i32, i32* %ret_, align 4, !dbg !69
  %cmp1 = icmp ne i32 %4, 0, !dbg !69
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !69

if.then2:                                         ; preds = %do.body
  %5 = load i32, i32* %ret_, align 4, !dbg !71
  store i32 %5, i32* %retval, align 4, !dbg !71
  br label %return, !dbg !71

if.end3:                                          ; preds = %do.body
  br label %do.end, !dbg !74

do.end:                                           ; preds = %if.end3
  %6 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !76
  %id4 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %6, i32 0, i32 0, !dbg !77
  %7 = load i64, i64* %id4, align 8, !dbg !77
  %call5 = call i32 @lzma_vli_size(i64 %7) #5, !dbg !78
  %8 = load i32*, i32** %size.addr, align 8, !dbg !79
  %9 = load i32, i32* %8, align 4, !dbg !80
  %conv = zext i32 %9 to i64, !dbg !80
  %call6 = call i32 @lzma_vli_size(i64 %conv) #5, !dbg !81
  %add = add i32 %call5, %call6, !dbg !83
  %10 = load i32*, i32** %size.addr, align 8, !dbg !84
  %11 = load i32, i32* %10, align 4, !dbg !85
  %add7 = add i32 %11, %add, !dbg !85
  store i32 %add7, i32* %10, align 4, !dbg !85
  store i32 0, i32* %retval, align 4, !dbg !86
  br label %return, !dbg !86

return:                                           ; preds = %do.end, %if.then2, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !87
  ret i32 %12, !dbg !87
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i32 @lzma_properties_size(i32*, %struct.lzma_filter*) #2

; Function Attrs: nounwind readonly
declare i32 @lzma_vli_size(i64) #3

; Function Attrs: nounwind uwtable
define i32 @lzma_filter_flags_encode(%struct.lzma_filter* %filter, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !41 {
entry:
  %retval = alloca i32, align 4
  %filter.addr = alloca %struct.lzma_filter*, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %props_size = alloca i32, align 4
  %ret_ = alloca i32, align 4
  %ret_6 = alloca i32, align 4
  %ret_13 = alloca i32, align 4
  %ret_26 = alloca i32, align 4
  store %struct.lzma_filter* %filter, %struct.lzma_filter** %filter.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filter.addr, metadata !88, metadata !54), !dbg !89
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !90, metadata !54), !dbg !91
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !92, metadata !54), !dbg !93
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !94, metadata !54), !dbg !95
  call void @llvm.dbg.declare(metadata i32* %props_size, metadata !96, metadata !54), !dbg !97
  %0 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !98
  %id = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %0, i32 0, i32 0, !dbg !100
  %1 = load i64, i64* %id, align 8, !dbg !100
  %cmp = icmp uge i64 %1, 4611686018427387904, !dbg !101
  br i1 %cmp, label %if.then, label %if.end, !dbg !102

if.then:                                          ; preds = %entry
  store i32 11, i32* %retval, align 4, !dbg !103
  br label %return, !dbg !103

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !104

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !105, metadata !54), !dbg !107
  %2 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !108
  %id1 = getelementptr inbounds %struct.lzma_filter, %struct.lzma_filter* %2, i32 0, i32 0, !dbg !108
  %3 = load i64, i64* %id1, align 8, !dbg !108
  %4 = load i8*, i8** %out.addr, align 8, !dbg !108
  %5 = load i64*, i64** %out_pos.addr, align 8, !dbg !108
  %6 = load i64, i64* %out_size.addr, align 8, !dbg !108
  %call = call i32 @lzma_vli_encode(i64 %3, i64* null, i8* %4, i64* %5, i64 %6) #4, !dbg !108
  store i32 %call, i32* %ret_, align 4, !dbg !108
  %7 = load i32, i32* %ret_, align 4, !dbg !108
  %cmp2 = icmp ne i32 %7, 0, !dbg !108
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !108

if.then3:                                         ; preds = %do.body
  %8 = load i32, i32* %ret_, align 4, !dbg !110
  store i32 %8, i32* %retval, align 4, !dbg !110
  br label %return, !dbg !110

if.end4:                                          ; preds = %do.body
  br label %do.end, !dbg !113

do.end:                                           ; preds = %if.end4
  br label %do.body5, !dbg !115

do.body5:                                         ; preds = %do.end
  call void @llvm.dbg.declare(metadata i32* %ret_6, metadata !116, metadata !54), !dbg !118
  %9 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !119
  %call7 = call i32 @lzma_properties_size(i32* %props_size, %struct.lzma_filter* %9) #4, !dbg !119
  store i32 %call7, i32* %ret_6, align 4, !dbg !119
  %10 = load i32, i32* %ret_6, align 4, !dbg !119
  %cmp8 = icmp ne i32 %10, 0, !dbg !119
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !119

if.then9:                                         ; preds = %do.body5
  %11 = load i32, i32* %ret_6, align 4, !dbg !121
  store i32 %11, i32* %retval, align 4, !dbg !121
  br label %return, !dbg !121

if.end10:                                         ; preds = %do.body5
  br label %do.end11, !dbg !124

do.end11:                                         ; preds = %if.end10
  br label %do.body12, !dbg !126

do.body12:                                        ; preds = %do.end11
  call void @llvm.dbg.declare(metadata i32* %ret_13, metadata !127, metadata !54), !dbg !129
  %12 = load i32, i32* %props_size, align 4, !dbg !130
  %conv = zext i32 %12 to i64, !dbg !130
  %13 = load i8*, i8** %out.addr, align 8, !dbg !130
  %14 = load i64*, i64** %out_pos.addr, align 8, !dbg !130
  %15 = load i64, i64* %out_size.addr, align 8, !dbg !130
  %call14 = call i32 @lzma_vli_encode(i64 %conv, i64* null, i8* %13, i64* %14, i64 %15) #4, !dbg !130
  store i32 %call14, i32* %ret_13, align 4, !dbg !130
  %16 = load i32, i32* %ret_13, align 4, !dbg !130
  %cmp15 = icmp ne i32 %16, 0, !dbg !130
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !130

if.then17:                                        ; preds = %do.body12
  %17 = load i32, i32* %ret_13, align 4, !dbg !132
  store i32 %17, i32* %retval, align 4, !dbg !132
  br label %return, !dbg !132

if.end18:                                         ; preds = %do.body12
  br label %do.end19, !dbg !135

do.end19:                                         ; preds = %if.end18
  %18 = load i64, i64* %out_size.addr, align 8, !dbg !137
  %19 = load i64*, i64** %out_pos.addr, align 8, !dbg !139
  %20 = load i64, i64* %19, align 8, !dbg !140
  %sub = sub i64 %18, %20, !dbg !141
  %21 = load i32, i32* %props_size, align 4, !dbg !142
  %conv20 = zext i32 %21 to i64, !dbg !142
  %cmp21 = icmp ult i64 %sub, %conv20, !dbg !143
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !144

if.then23:                                        ; preds = %do.end19
  store i32 11, i32* %retval, align 4, !dbg !145
  br label %return, !dbg !145

if.end24:                                         ; preds = %do.end19
  br label %do.body25, !dbg !146

do.body25:                                        ; preds = %if.end24
  call void @llvm.dbg.declare(metadata i32* %ret_26, metadata !147, metadata !54), !dbg !149
  %22 = load %struct.lzma_filter*, %struct.lzma_filter** %filter.addr, align 8, !dbg !150
  %23 = load i8*, i8** %out.addr, align 8, !dbg !150
  %24 = load i64*, i64** %out_pos.addr, align 8, !dbg !150
  %25 = load i64, i64* %24, align 8, !dbg !150
  %add.ptr = getelementptr inbounds i8, i8* %23, i64 %25, !dbg !150
  %call27 = call i32 @lzma_properties_encode(%struct.lzma_filter* %22, i8* %add.ptr) #4, !dbg !150
  store i32 %call27, i32* %ret_26, align 4, !dbg !150
  %26 = load i32, i32* %ret_26, align 4, !dbg !150
  %cmp28 = icmp ne i32 %26, 0, !dbg !150
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !150

if.then30:                                        ; preds = %do.body25
  %27 = load i32, i32* %ret_26, align 4, !dbg !152
  store i32 %27, i32* %retval, align 4, !dbg !152
  br label %return, !dbg !152

if.end31:                                         ; preds = %do.body25
  br label %do.end32, !dbg !155

do.end32:                                         ; preds = %if.end31
  %28 = load i32, i32* %props_size, align 4, !dbg !157
  %conv33 = zext i32 %28 to i64, !dbg !157
  %29 = load i64*, i64** %out_pos.addr, align 8, !dbg !158
  %30 = load i64, i64* %29, align 8, !dbg !159
  %add = add i64 %30, %conv33, !dbg !159
  store i64 %add, i64* %29, align 8, !dbg !159
  store i32 0, i32* %retval, align 4, !dbg !160
  br label %return, !dbg !160

return:                                           ; preds = %do.end32, %if.then30, %if.then23, %if.then17, %if.then9, %if.then3, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !161
  ret i32 %31, !dbg !161
}

; Function Attrs: nounwind
declare i32 @lzma_vli_encode(i64, i64*, i8*, i64*, i64) #2

; Function Attrs: nounwind
declare i32 @lzma_properties_encode(%struct.lzma_filter*, i8*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!50, !51}
!llvm.ident = !{!52}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !18)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_flags_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
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
!18 = !{!19, !41}
!19 = distinct !DISubprogram(name: "lzma_filter_flags_size", scope: !1, file: !1, line: 17, type: !20, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !40)
!20 = !DISubroutineType(types: !21)
!21 = !{!22, !23, !27}
!22 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64, align: 64)
!24 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !25, line: 51, baseType: !26)
!25 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !29)
!29 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !30, line: 65, baseType: !31)
!30 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!31 = !DICompositeType(tag: DW_TAG_structure_type, file: !30, line: 43, size: 128, align: 64, elements: !32)
!32 = !{!33, !38}
!33 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !31, file: !30, line: 54, baseType: !34, size: 64, align: 64)
!34 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !35, line: 63, baseType: !36)
!35 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!36 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !25, line: 55, baseType: !37)
!37 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !31, file: !30, line: 63, baseType: !39, size: 64, align: 64, offset: 64)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!40 = !{}
!41 = distinct !DISubprogram(name: "lzma_filter_flags_encode", scope: !1, file: !1, line: 31, type: !42, isLocal: false, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !40)
!42 = !DISubroutineType(types: !43)
!43 = !{!22, !27, !44, !47, !48}
!44 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !25, line: 48, baseType: !46)
!46 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !49, line: 62, baseType: !37)
!49 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!50 = !{i32 2, !"Dwarf Version", i32 4}
!51 = !{i32 2, !"Debug Info Version", i32 3}
!52 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!53 = !DILocalVariable(name: "size", arg: 1, scope: !19, file: !1, line: 17, type: !23)
!54 = !DIExpression()
!55 = !DILocation(line: 17, column: 34, scope: !19)
!56 = !DILocalVariable(name: "filter", arg: 2, scope: !19, file: !1, line: 17, type: !27)
!57 = !DILocation(line: 17, column: 59, scope: !19)
!58 = !DILocation(line: 19, column: 6, scope: !59)
!59 = distinct !DILexicalBlock(scope: !19, file: !1, line: 19, column: 6)
!60 = !DILocation(line: 19, column: 14, scope: !59)
!61 = !DILocation(line: 19, column: 17, scope: !59)
!62 = !DILocation(line: 19, column: 6, scope: !19)
!63 = !DILocation(line: 20, column: 3, scope: !59)
!64 = !DILocation(line: 22, column: 2, scope: !19)
!65 = !DILocalVariable(name: "ret_", scope: !66, file: !1, line: 22, type: !67)
!66 = distinct !DILexicalBlock(scope: !19, file: !1, line: 22, column: 2)
!67 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !22)
!68 = !DILocation(line: 22, column: 2, scope: !66)
!69 = !DILocation(line: 22, column: 2, scope: !70)
!70 = !DILexicalBlockFile(scope: !66, file: !1, discriminator: 1)
!71 = !DILocation(line: 22, column: 2, scope: !72)
!72 = !DILexicalBlockFile(scope: !73, file: !1, discriminator: 2)
!73 = distinct !DILexicalBlock(scope: !66, file: !1, line: 22, column: 2)
!74 = !DILocation(line: 22, column: 2, scope: !75)
!75 = !DILexicalBlockFile(scope: !66, file: !1, discriminator: 3)
!76 = !DILocation(line: 24, column: 25, scope: !19)
!77 = !DILocation(line: 24, column: 33, scope: !19)
!78 = !DILocation(line: 24, column: 11, scope: !19)
!79 = !DILocation(line: 24, column: 54, scope: !19)
!80 = !DILocation(line: 24, column: 53, scope: !19)
!81 = !DILocation(line: 24, column: 39, scope: !82)
!82 = !DILexicalBlockFile(scope: !19, file: !1, discriminator: 1)
!83 = !DILocation(line: 24, column: 37, scope: !19)
!84 = !DILocation(line: 24, column: 3, scope: !19)
!85 = !DILocation(line: 24, column: 8, scope: !19)
!86 = !DILocation(line: 26, column: 2, scope: !19)
!87 = !DILocation(line: 27, column: 1, scope: !19)
!88 = !DILocalVariable(name: "filter", arg: 1, scope: !41, file: !1, line: 31, type: !27)
!89 = !DILocation(line: 31, column: 45, scope: !41)
!90 = !DILocalVariable(name: "out", arg: 2, scope: !41, file: !1, line: 32, type: !44)
!91 = !DILocation(line: 32, column: 12, scope: !41)
!92 = !DILocalVariable(name: "out_pos", arg: 3, scope: !41, file: !1, line: 32, type: !47)
!93 = !DILocation(line: 32, column: 25, scope: !41)
!94 = !DILocalVariable(name: "out_size", arg: 4, scope: !41, file: !1, line: 32, type: !48)
!95 = !DILocation(line: 32, column: 41, scope: !41)
!96 = !DILocalVariable(name: "props_size", scope: !41, file: !1, line: 34, type: !24)
!97 = !DILocation(line: 34, column: 11, scope: !41)
!98 = !DILocation(line: 37, column: 6, scope: !99)
!99 = distinct !DILexicalBlock(scope: !41, file: !1, line: 37, column: 6)
!100 = !DILocation(line: 37, column: 14, scope: !99)
!101 = !DILocation(line: 37, column: 17, scope: !99)
!102 = !DILocation(line: 37, column: 6, scope: !41)
!103 = !DILocation(line: 38, column: 3, scope: !99)
!104 = !DILocation(line: 40, column: 2, scope: !41)
!105 = !DILocalVariable(name: "ret_", scope: !106, file: !1, line: 40, type: !67)
!106 = distinct !DILexicalBlock(scope: !41, file: !1, line: 40, column: 2)
!107 = !DILocation(line: 40, column: 2, scope: !106)
!108 = !DILocation(line: 40, column: 2, scope: !109)
!109 = !DILexicalBlockFile(scope: !106, file: !1, discriminator: 1)
!110 = !DILocation(line: 40, column: 2, scope: !111)
!111 = !DILexicalBlockFile(scope: !112, file: !1, discriminator: 2)
!112 = distinct !DILexicalBlock(scope: !106, file: !1, line: 40, column: 2)
!113 = !DILocation(line: 40, column: 2, scope: !114)
!114 = !DILexicalBlockFile(scope: !106, file: !1, discriminator: 3)
!115 = !DILocation(line: 44, column: 2, scope: !41)
!116 = !DILocalVariable(name: "ret_", scope: !117, file: !1, line: 44, type: !67)
!117 = distinct !DILexicalBlock(scope: !41, file: !1, line: 44, column: 2)
!118 = !DILocation(line: 44, column: 2, scope: !117)
!119 = !DILocation(line: 44, column: 2, scope: !120)
!120 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 1)
!121 = !DILocation(line: 44, column: 2, scope: !122)
!122 = !DILexicalBlockFile(scope: !123, file: !1, discriminator: 2)
!123 = distinct !DILexicalBlock(scope: !117, file: !1, line: 44, column: 2)
!124 = !DILocation(line: 44, column: 2, scope: !125)
!125 = !DILexicalBlockFile(scope: !117, file: !1, discriminator: 3)
!126 = !DILocation(line: 45, column: 2, scope: !41)
!127 = !DILocalVariable(name: "ret_", scope: !128, file: !1, line: 45, type: !67)
!128 = distinct !DILexicalBlock(scope: !41, file: !1, line: 45, column: 2)
!129 = !DILocation(line: 45, column: 2, scope: !128)
!130 = !DILocation(line: 45, column: 2, scope: !131)
!131 = !DILexicalBlockFile(scope: !128, file: !1, discriminator: 1)
!132 = !DILocation(line: 45, column: 2, scope: !133)
!133 = !DILexicalBlockFile(scope: !134, file: !1, discriminator: 2)
!134 = distinct !DILexicalBlock(scope: !128, file: !1, line: 45, column: 2)
!135 = !DILocation(line: 45, column: 2, scope: !136)
!136 = !DILexicalBlockFile(scope: !128, file: !1, discriminator: 3)
!137 = !DILocation(line: 49, column: 6, scope: !138)
!138 = distinct !DILexicalBlock(scope: !41, file: !1, line: 49, column: 6)
!139 = !DILocation(line: 49, column: 18, scope: !138)
!140 = !DILocation(line: 49, column: 17, scope: !138)
!141 = !DILocation(line: 49, column: 15, scope: !138)
!142 = !DILocation(line: 49, column: 28, scope: !138)
!143 = !DILocation(line: 49, column: 26, scope: !138)
!144 = !DILocation(line: 49, column: 6, scope: !41)
!145 = !DILocation(line: 50, column: 3, scope: !138)
!146 = !DILocation(line: 52, column: 2, scope: !41)
!147 = !DILocalVariable(name: "ret_", scope: !148, file: !1, line: 52, type: !67)
!148 = distinct !DILexicalBlock(scope: !41, file: !1, line: 52, column: 2)
!149 = !DILocation(line: 52, column: 2, scope: !148)
!150 = !DILocation(line: 52, column: 2, scope: !151)
!151 = !DILexicalBlockFile(scope: !148, file: !1, discriminator: 1)
!152 = !DILocation(line: 52, column: 2, scope: !153)
!153 = !DILexicalBlockFile(scope: !154, file: !1, discriminator: 2)
!154 = distinct !DILexicalBlock(scope: !148, file: !1, line: 52, column: 2)
!155 = !DILocation(line: 52, column: 2, scope: !156)
!156 = !DILexicalBlockFile(scope: !148, file: !1, discriminator: 3)
!157 = !DILocation(line: 54, column: 14, scope: !41)
!158 = !DILocation(line: 54, column: 3, scope: !41)
!159 = !DILocation(line: 54, column: 11, scope: !41)
!160 = !DILocation(line: 56, column: 2, scope: !41)
!161 = !DILocation(line: 57, column: 1, scope: !41)
