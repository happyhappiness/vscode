; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmzlib/uncompr.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.internal_state = type { i32 }

@.str = private unnamed_addr constant [6 x i8] c"1.2.3\00", align 1

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_uncompress(i8* %dest, i64* %destLen, i8* %source, i64 %sourceLen) #0 !dbg !25 {
entry:
  %retval = alloca i32, align 4
  %dest.addr = alloca i8*, align 8
  %destLen.addr = alloca i64*, align 8
  %source.addr = alloca i8*, align 8
  %sourceLen.addr = alloca i64, align 8
  %stream = alloca %struct.z_stream_s, align 8
  %err = alloca i32, align 4
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !36, metadata !37), !dbg !38
  store i64* %destLen, i64** %destLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %destLen.addr, metadata !39, metadata !37), !dbg !40
  store i8* %source, i8** %source.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %source.addr, metadata !41, metadata !37), !dbg !42
  store i64 %sourceLen, i64* %sourceLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sourceLen.addr, metadata !43, metadata !37), !dbg !44
  call void @llvm.dbg.declare(metadata %struct.z_stream_s* %stream, metadata !45, metadata !37), !dbg !69
  call void @llvm.dbg.declare(metadata i32* %err, metadata !70, metadata !37), !dbg !71
  %0 = load i8*, i8** %source.addr, align 8, !dbg !72
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 0, !dbg !73
  store i8* %0, i8** %next_in, align 8, !dbg !74
  %1 = load i64, i64* %sourceLen.addr, align 8, !dbg !75
  %conv = trunc i64 %1 to i32, !dbg !76
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !77
  store i32 %conv, i32* %avail_in, align 8, !dbg !78
  %avail_in1 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !79
  %2 = load i32, i32* %avail_in1, align 8, !dbg !79
  %conv2 = zext i32 %2 to i64, !dbg !81
  %3 = load i64, i64* %sourceLen.addr, align 8, !dbg !82
  %cmp = icmp ne i64 %conv2, %3, !dbg !83
  br i1 %cmp, label %if.then, label %if.end, !dbg !84

if.then:                                          ; preds = %entry
  store i32 -5, i32* %retval, align 4, !dbg !85
  br label %return, !dbg !85

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %dest.addr, align 8, !dbg !87
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 3, !dbg !88
  store i8* %4, i8** %next_out, align 8, !dbg !89
  %5 = load i64*, i64** %destLen.addr, align 8, !dbg !90
  %6 = load i64, i64* %5, align 8, !dbg !91
  %conv4 = trunc i64 %6 to i32, !dbg !92
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 4, !dbg !93
  store i32 %conv4, i32* %avail_out, align 8, !dbg !94
  %avail_out5 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 4, !dbg !95
  %7 = load i32, i32* %avail_out5, align 8, !dbg !95
  %conv6 = zext i32 %7 to i64, !dbg !97
  %8 = load i64*, i64** %destLen.addr, align 8, !dbg !98
  %9 = load i64, i64* %8, align 8, !dbg !99
  %cmp7 = icmp ne i64 %conv6, %9, !dbg !100
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !101

if.then9:                                         ; preds = %if.end
  store i32 -5, i32* %retval, align 4, !dbg !102
  br label %return, !dbg !102

if.end10:                                         ; preds = %if.end
  %zalloc = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 8, !dbg !104
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %zalloc, align 8, !dbg !105
  %zfree = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 9, !dbg !106
  store void (i8*, i8*)* null, void (i8*, i8*)** %zfree, align 8, !dbg !107
  %call = call i32 @cm_zlib_inflateInit_(%struct.z_stream_s* %stream, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), i32 112), !dbg !108
  store i32 %call, i32* %err, align 4, !dbg !109
  %10 = load i32, i32* %err, align 4, !dbg !110
  %cmp11 = icmp ne i32 %10, 0, !dbg !112
  br i1 %cmp11, label %if.then13, label %if.end14, !dbg !113

if.then13:                                        ; preds = %if.end10
  %11 = load i32, i32* %err, align 4, !dbg !114
  store i32 %11, i32* %retval, align 4, !dbg !116
  br label %return, !dbg !116

if.end14:                                         ; preds = %if.end10
  %call15 = call i32 @cm_zlib_inflate(%struct.z_stream_s* %stream, i32 4), !dbg !117
  store i32 %call15, i32* %err, align 4, !dbg !118
  %12 = load i32, i32* %err, align 4, !dbg !119
  %cmp16 = icmp ne i32 %12, 1, !dbg !121
  br i1 %cmp16, label %if.then18, label %if.end29, !dbg !122

if.then18:                                        ; preds = %if.end14
  %call19 = call i32 @cm_zlib_inflateEnd(%struct.z_stream_s* %stream), !dbg !123
  %13 = load i32, i32* %err, align 4, !dbg !125
  %cmp20 = icmp eq i32 %13, 2, !dbg !127
  br i1 %cmp20, label %if.then27, label %lor.lhs.false, !dbg !128

lor.lhs.false:                                    ; preds = %if.then18
  %14 = load i32, i32* %err, align 4, !dbg !129
  %cmp22 = icmp eq i32 %14, -5, !dbg !131
  br i1 %cmp22, label %land.lhs.true, label %if.end28, !dbg !132

land.lhs.true:                                    ; preds = %lor.lhs.false
  %avail_in24 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !133
  %15 = load i32, i32* %avail_in24, align 8, !dbg !133
  %cmp25 = icmp eq i32 %15, 0, !dbg !135
  br i1 %cmp25, label %if.then27, label %if.end28, !dbg !136

if.then27:                                        ; preds = %land.lhs.true, %if.then18
  store i32 -3, i32* %retval, align 4, !dbg !137
  br label %return, !dbg !137

if.end28:                                         ; preds = %land.lhs.true, %lor.lhs.false
  %16 = load i32, i32* %err, align 4, !dbg !138
  store i32 %16, i32* %retval, align 4, !dbg !139
  br label %return, !dbg !139

if.end29:                                         ; preds = %if.end14
  %total_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 5, !dbg !140
  %17 = load i64, i64* %total_out, align 8, !dbg !140
  %18 = load i64*, i64** %destLen.addr, align 8, !dbg !141
  store i64 %17, i64* %18, align 8, !dbg !142
  %call30 = call i32 @cm_zlib_inflateEnd(%struct.z_stream_s* %stream), !dbg !143
  store i32 %call30, i32* %err, align 4, !dbg !144
  %19 = load i32, i32* %err, align 4, !dbg !145
  store i32 %19, i32* %retval, align 4, !dbg !146
  br label %return, !dbg !146

return:                                           ; preds = %if.end29, %if.end28, %if.then27, %if.then13, %if.then9, %if.then
  %20 = load i32, i32* %retval, align 4, !dbg !147
  ret i32 %20, !dbg !147
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @cm_zlib_inflateInit_(%struct.z_stream_s*, i8*, i32) #2

declare i32 @cm_zlib_inflate(%struct.z_stream_s*, i32) #2

declare i32 @cm_zlib_inflateEnd(%struct.z_stream_s*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!33, !34}
!llvm.ident = !{!35}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !24)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/uncompr.c", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!2 = !{}
!3 = !{!4, !9, !11, !13, !20}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bytef", file: !6, line: 276, baseType: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zconf.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!7 = !DIDerivedType(tag: DW_TAG_typedef, name: "Byte", file: !6, line: 267, baseType: !8)
!8 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "uInt", file: !6, line: 269, baseType: !10)
!10 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!11 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLong", file: !6, line: 270, baseType: !12)
!12 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!13 = !DIDerivedType(tag: DW_TAG_typedef, name: "alloc_func", file: !14, line: 77, baseType: !15)
!14 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/zlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!16 = !DISubroutineType(types: !17)
!17 = !{!18, !18, !9, !9}
!18 = !DIDerivedType(tag: DW_TAG_typedef, name: "voidpf", file: !6, line: 285, baseType: !19)
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "free_func", file: !14, line: 78, baseType: !21)
!21 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !22, size: 64, align: 64)
!22 = !DISubroutineType(types: !23)
!23 = !{null, !18, !18}
!24 = !{!25}
!25 = distinct !DISubprogram(name: "cm_zlib_uncompress", scope: !1, file: !1, line: 26, type: !26, isLocal: false, isDefinition: true, scopeLine: 31, isOptimized: false, variables: !2)
!26 = !DISubroutineType(types: !27)
!27 = !{!28, !4, !29, !31, !11}
!28 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLongf", file: !6, line: 281, baseType: !11)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !5)
!33 = !{i32 2, !"Dwarf Version", i32 4}
!34 = !{i32 2, !"Debug Info Version", i32 3}
!35 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!36 = !DILocalVariable(name: "dest", arg: 1, scope: !25, file: !1, line: 27, type: !4)
!37 = !DIExpression()
!38 = !DILocation(line: 27, column: 12, scope: !25)
!39 = !DILocalVariable(name: "destLen", arg: 2, scope: !25, file: !1, line: 28, type: !29)
!40 = !DILocation(line: 28, column: 13, scope: !25)
!41 = !DILocalVariable(name: "source", arg: 3, scope: !25, file: !1, line: 29, type: !31)
!42 = !DILocation(line: 29, column: 18, scope: !25)
!43 = !DILocalVariable(name: "sourceLen", arg: 4, scope: !25, file: !1, line: 30, type: !11)
!44 = !DILocation(line: 30, column: 11, scope: !25)
!45 = !DILocalVariable(name: "stream", scope: !25, file: !1, line: 32, type: !46)
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !14, line: 101, baseType: !47)
!47 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !14, line: 82, size: 896, align: 64, elements: !48)
!48 = !{!49, !50, !51, !52, !53, !54, !55, !58, !63, !64, !65, !66, !67, !68}
!49 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !47, file: !14, line: 83, baseType: !4, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !47, file: !14, line: 84, baseType: !9, size: 32, align: 32, offset: 64)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !47, file: !14, line: 85, baseType: !11, size: 64, align: 64, offset: 128)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !47, file: !14, line: 87, baseType: !4, size: 64, align: 64, offset: 192)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !47, file: !14, line: 88, baseType: !9, size: 32, align: 32, offset: 256)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !47, file: !14, line: 89, baseType: !11, size: 64, align: 64, offset: 320)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !47, file: !14, line: 91, baseType: !56, size: 64, align: 64, offset: 384)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !47, file: !14, line: 92, baseType: !59, size: 64, align: 64, offset: 448)
!59 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !60, size: 64, align: 64)
!60 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !14, line: 1346, size: 32, align: 32, elements: !61)
!61 = !{!62}
!62 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !60, file: !14, line: 1346, baseType: !28, size: 32, align: 32)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !47, file: !14, line: 94, baseType: !13, size: 64, align: 64, offset: 512)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !47, file: !14, line: 95, baseType: !20, size: 64, align: 64, offset: 576)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !47, file: !14, line: 96, baseType: !18, size: 64, align: 64, offset: 640)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !47, file: !14, line: 98, baseType: !28, size: 32, align: 32, offset: 704)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !47, file: !14, line: 99, baseType: !11, size: 64, align: 64, offset: 768)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !47, file: !14, line: 100, baseType: !11, size: 64, align: 64, offset: 832)
!69 = !DILocation(line: 32, column: 14, scope: !25)
!70 = !DILocalVariable(name: "err", scope: !25, file: !1, line: 33, type: !28)
!71 = !DILocation(line: 33, column: 9, scope: !25)
!72 = !DILocation(line: 35, column: 30, scope: !25)
!73 = !DILocation(line: 35, column: 12, scope: !25)
!74 = !DILocation(line: 35, column: 20, scope: !25)
!75 = !DILocation(line: 36, column: 29, scope: !25)
!76 = !DILocation(line: 36, column: 23, scope: !25)
!77 = !DILocation(line: 36, column: 12, scope: !25)
!78 = !DILocation(line: 36, column: 21, scope: !25)
!79 = !DILocation(line: 38, column: 23, scope: !80)
!80 = distinct !DILexicalBlock(scope: !25, file: !1, line: 38, column: 9)
!81 = !DILocation(line: 38, column: 9, scope: !80)
!82 = !DILocation(line: 38, column: 35, scope: !80)
!83 = !DILocation(line: 38, column: 32, scope: !80)
!84 = !DILocation(line: 38, column: 9, scope: !25)
!85 = !DILocation(line: 38, column: 46, scope: !86)
!86 = !DILexicalBlockFile(scope: !80, file: !1, discriminator: 1)
!87 = !DILocation(line: 40, column: 23, scope: !25)
!88 = !DILocation(line: 40, column: 12, scope: !25)
!89 = !DILocation(line: 40, column: 21, scope: !25)
!90 = !DILocation(line: 41, column: 31, scope: !25)
!91 = !DILocation(line: 41, column: 30, scope: !25)
!92 = !DILocation(line: 41, column: 24, scope: !25)
!93 = !DILocation(line: 41, column: 12, scope: !25)
!94 = !DILocation(line: 41, column: 22, scope: !25)
!95 = !DILocation(line: 42, column: 23, scope: !96)
!96 = distinct !DILexicalBlock(scope: !25, file: !1, line: 42, column: 9)
!97 = !DILocation(line: 42, column: 9, scope: !96)
!98 = !DILocation(line: 42, column: 37, scope: !96)
!99 = !DILocation(line: 42, column: 36, scope: !96)
!100 = !DILocation(line: 42, column: 33, scope: !96)
!101 = !DILocation(line: 42, column: 9, scope: !25)
!102 = !DILocation(line: 42, column: 46, scope: !103)
!103 = !DILexicalBlockFile(scope: !96, file: !1, discriminator: 1)
!104 = !DILocation(line: 44, column: 12, scope: !25)
!105 = !DILocation(line: 44, column: 19, scope: !25)
!106 = !DILocation(line: 45, column: 12, scope: !25)
!107 = !DILocation(line: 45, column: 18, scope: !25)
!108 = !DILocation(line: 47, column: 11, scope: !25)
!109 = !DILocation(line: 47, column: 9, scope: !25)
!110 = !DILocation(line: 48, column: 9, scope: !111)
!111 = distinct !DILexicalBlock(scope: !25, file: !1, line: 48, column: 9)
!112 = !DILocation(line: 48, column: 13, scope: !111)
!113 = !DILocation(line: 48, column: 9, scope: !25)
!114 = !DILocation(line: 48, column: 29, scope: !115)
!115 = !DILexicalBlockFile(scope: !111, file: !1, discriminator: 1)
!116 = !DILocation(line: 48, column: 22, scope: !115)
!117 = !DILocation(line: 50, column: 11, scope: !25)
!118 = !DILocation(line: 50, column: 9, scope: !25)
!119 = !DILocation(line: 51, column: 9, scope: !120)
!120 = distinct !DILexicalBlock(scope: !25, file: !1, line: 51, column: 9)
!121 = !DILocation(line: 51, column: 13, scope: !120)
!122 = !DILocation(line: 51, column: 9, scope: !25)
!123 = !DILocation(line: 52, column: 9, scope: !124)
!124 = distinct !DILexicalBlock(scope: !120, file: !1, line: 51, column: 30)
!125 = !DILocation(line: 53, column: 13, scope: !126)
!126 = distinct !DILexicalBlock(scope: !124, file: !1, line: 53, column: 13)
!127 = !DILocation(line: 53, column: 17, scope: !126)
!128 = !DILocation(line: 53, column: 32, scope: !126)
!129 = !DILocation(line: 53, column: 36, scope: !130)
!130 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 1)
!131 = !DILocation(line: 53, column: 40, scope: !130)
!132 = !DILocation(line: 53, column: 55, scope: !130)
!133 = !DILocation(line: 53, column: 65, scope: !134)
!134 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 2)
!135 = !DILocation(line: 53, column: 74, scope: !134)
!136 = !DILocation(line: 53, column: 13, scope: !134)
!137 = !DILocation(line: 54, column: 13, scope: !126)
!138 = !DILocation(line: 55, column: 16, scope: !124)
!139 = !DILocation(line: 55, column: 9, scope: !124)
!140 = !DILocation(line: 57, column: 23, scope: !25)
!141 = !DILocation(line: 57, column: 6, scope: !25)
!142 = !DILocation(line: 57, column: 14, scope: !25)
!143 = !DILocation(line: 59, column: 11, scope: !25)
!144 = !DILocation(line: 59, column: 9, scope: !25)
!145 = !DILocation(line: 60, column: 12, scope: !25)
!146 = !DILocation(line: 60, column: 5, scope: !25)
!147 = !DILocation(line: 61, column: 1, scope: !25)
