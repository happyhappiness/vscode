; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmzlib/compress.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.z_stream_s = type { i8*, i32, i64, i8*, i32, i64, i8*, %struct.internal_state*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8*, i32, i64, i64 }
%struct.internal_state = type { i32 }

@.str = private unnamed_addr constant [6 x i8] c"1.2.3\00", align 1

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_compress2(i8* %dest, i64* %destLen, i8* %source, i64 %sourceLen, i32 %level) #0 !dbg !25 {
entry:
  %retval = alloca i32, align 4
  %dest.addr = alloca i8*, align 8
  %destLen.addr = alloca i64*, align 8
  %source.addr = alloca i8*, align 8
  %sourceLen.addr = alloca i64, align 8
  %level.addr = alloca i32, align 4
  %stream = alloca %struct.z_stream_s, align 8
  %err = alloca i32, align 4
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !42, metadata !43), !dbg !44
  store i64* %destLen, i64** %destLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %destLen.addr, metadata !45, metadata !43), !dbg !46
  store i8* %source, i8** %source.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %source.addr, metadata !47, metadata !43), !dbg !48
  store i64 %sourceLen, i64* %sourceLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sourceLen.addr, metadata !49, metadata !43), !dbg !50
  store i32 %level, i32* %level.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %level.addr, metadata !51, metadata !43), !dbg !52
  call void @llvm.dbg.declare(metadata %struct.z_stream_s* %stream, metadata !53, metadata !43), !dbg !77
  call void @llvm.dbg.declare(metadata i32* %err, metadata !78, metadata !43), !dbg !79
  %0 = load i8*, i8** %source.addr, align 8, !dbg !80
  %next_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 0, !dbg !81
  store i8* %0, i8** %next_in, align 8, !dbg !82
  %1 = load i64, i64* %sourceLen.addr, align 8, !dbg !83
  %conv = trunc i64 %1 to i32, !dbg !84
  %avail_in = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 1, !dbg !85
  store i32 %conv, i32* %avail_in, align 8, !dbg !86
  %2 = load i8*, i8** %dest.addr, align 8, !dbg !87
  %next_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 3, !dbg !88
  store i8* %2, i8** %next_out, align 8, !dbg !89
  %3 = load i64*, i64** %destLen.addr, align 8, !dbg !90
  %4 = load i64, i64* %3, align 8, !dbg !91
  %conv1 = trunc i64 %4 to i32, !dbg !92
  %avail_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 4, !dbg !93
  store i32 %conv1, i32* %avail_out, align 8, !dbg !94
  %avail_out2 = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 4, !dbg !95
  %5 = load i32, i32* %avail_out2, align 8, !dbg !95
  %conv3 = zext i32 %5 to i64, !dbg !97
  %6 = load i64*, i64** %destLen.addr, align 8, !dbg !98
  %7 = load i64, i64* %6, align 8, !dbg !99
  %cmp = icmp ne i64 %conv3, %7, !dbg !100
  br i1 %cmp, label %if.then, label %if.end, !dbg !101

if.then:                                          ; preds = %entry
  store i32 -5, i32* %retval, align 4, !dbg !102
  br label %return, !dbg !102

if.end:                                           ; preds = %entry
  %zalloc = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 8, !dbg !104
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %zalloc, align 8, !dbg !105
  %zfree = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 9, !dbg !106
  store void (i8*, i8*)* null, void (i8*, i8*)** %zfree, align 8, !dbg !107
  %opaque = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 10, !dbg !108
  store i8* null, i8** %opaque, align 8, !dbg !109
  %8 = load i32, i32* %level.addr, align 4, !dbg !110
  %call = call i32 @cm_zlib_deflateInit_(%struct.z_stream_s* %stream, i32 %8, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str, i32 0, i32 0), i32 112), !dbg !110
  store i32 %call, i32* %err, align 4, !dbg !111
  %9 = load i32, i32* %err, align 4, !dbg !112
  %cmp5 = icmp ne i32 %9, 0, !dbg !114
  br i1 %cmp5, label %if.then7, label %if.end8, !dbg !115

if.then7:                                         ; preds = %if.end
  %10 = load i32, i32* %err, align 4, !dbg !116
  store i32 %10, i32* %retval, align 4, !dbg !118
  br label %return, !dbg !118

if.end8:                                          ; preds = %if.end
  %call9 = call i32 @cm_zlib_deflate(%struct.z_stream_s* %stream, i32 4), !dbg !119
  store i32 %call9, i32* %err, align 4, !dbg !120
  %11 = load i32, i32* %err, align 4, !dbg !121
  %cmp10 = icmp ne i32 %11, 1, !dbg !123
  br i1 %cmp10, label %if.then12, label %if.end16, !dbg !124

if.then12:                                        ; preds = %if.end8
  %call13 = call i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %stream), !dbg !125
  %12 = load i32, i32* %err, align 4, !dbg !127
  %cmp14 = icmp eq i32 %12, 0, !dbg !128
  br i1 %cmp14, label %cond.true, label %cond.false, !dbg !127

cond.true:                                        ; preds = %if.then12
  br label %cond.end, !dbg !129

cond.false:                                       ; preds = %if.then12
  %13 = load i32, i32* %err, align 4, !dbg !131
  br label %cond.end, !dbg !133

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ -5, %cond.true ], [ %13, %cond.false ], !dbg !134
  store i32 %cond, i32* %retval, align 4, !dbg !136
  br label %return, !dbg !136

if.end16:                                         ; preds = %if.end8
  %total_out = getelementptr inbounds %struct.z_stream_s, %struct.z_stream_s* %stream, i32 0, i32 5, !dbg !137
  %14 = load i64, i64* %total_out, align 8, !dbg !137
  %15 = load i64*, i64** %destLen.addr, align 8, !dbg !138
  store i64 %14, i64* %15, align 8, !dbg !139
  %call17 = call i32 @cm_zlib_deflateEnd(%struct.z_stream_s* %stream), !dbg !140
  store i32 %call17, i32* %err, align 4, !dbg !141
  %16 = load i32, i32* %err, align 4, !dbg !142
  store i32 %16, i32* %retval, align 4, !dbg !143
  br label %return, !dbg !143

return:                                           ; preds = %if.end16, %cond.end, %if.then7, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !144
  ret i32 %17, !dbg !144
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @cm_zlib_deflateInit_(%struct.z_stream_s*, i32, i8*, i32) #2

declare i32 @cm_zlib_deflate(%struct.z_stream_s*, i32) #2

declare i32 @cm_zlib_deflateEnd(%struct.z_stream_s*) #2

; Function Attrs: nounwind uwtable
define i32 @cm_zlib_compress(i8* %dest, i64* %destLen, i8* %source, i64 %sourceLen) #0 !dbg !33 {
entry:
  %dest.addr = alloca i8*, align 8
  %destLen.addr = alloca i64*, align 8
  %source.addr = alloca i8*, align 8
  %sourceLen.addr = alloca i64, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !145, metadata !43), !dbg !146
  store i64* %destLen, i64** %destLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %destLen.addr, metadata !147, metadata !43), !dbg !148
  store i8* %source, i8** %source.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %source.addr, metadata !149, metadata !43), !dbg !150
  store i64 %sourceLen, i64* %sourceLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sourceLen.addr, metadata !151, metadata !43), !dbg !152
  %0 = load i8*, i8** %dest.addr, align 8, !dbg !153
  %1 = load i64*, i64** %destLen.addr, align 8, !dbg !154
  %2 = load i8*, i8** %source.addr, align 8, !dbg !155
  %3 = load i64, i64* %sourceLen.addr, align 8, !dbg !156
  %call = call i32 @cm_zlib_compress2(i8* %0, i64* %1, i8* %2, i64 %3, i32 -1), !dbg !157
  ret i32 %call, !dbg !158
}

; Function Attrs: nounwind uwtable
define i64 @cm_zlib_compressBound(i64 %sourceLen) #0 !dbg !36 {
entry:
  %sourceLen.addr = alloca i64, align 8
  store i64 %sourceLen, i64* %sourceLen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sourceLen.addr, metadata !159, metadata !43), !dbg !160
  %0 = load i64, i64* %sourceLen.addr, align 8, !dbg !161
  %1 = load i64, i64* %sourceLen.addr, align 8, !dbg !162
  %shr = lshr i64 %1, 12, !dbg !163
  %add = add i64 %0, %shr, !dbg !164
  %2 = load i64, i64* %sourceLen.addr, align 8, !dbg !165
  %shr1 = lshr i64 %2, 14, !dbg !166
  %add2 = add i64 %add, %shr1, !dbg !167
  %add3 = add i64 %add2, 11, !dbg !168
  ret i64 %add3, !dbg !169
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!39, !40}
!llvm.ident = !{!41}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !24)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmzlib/compress.c", directory: "/data/download/cmake/cmake-master/Utilities/cmzlib")
!2 = !{}
!3 = !{!4, !9, !11, !13, !20, !18}
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
!24 = !{!25, !33, !36}
!25 = distinct !DISubprogram(name: "cm_zlib_compress2", scope: !1, file: !1, line: 22, type: !26, isLocal: false, isDefinition: true, scopeLine: 28, isOptimized: false, variables: !2)
!26 = !DISubroutineType(types: !27)
!27 = !{!28, !4, !29, !31, !11, !28}
!28 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "uLongf", file: !6, line: 281, baseType: !11)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !5)
!33 = distinct !DISubprogram(name: "cm_zlib_compress", scope: !1, file: !1, line: 62, type: !34, isLocal: false, isDefinition: true, scopeLine: 67, isOptimized: false, variables: !2)
!34 = !DISubroutineType(types: !35)
!35 = !{!28, !4, !29, !31, !11}
!36 = distinct !DISubprogram(name: "cm_zlib_compressBound", scope: !1, file: !1, line: 75, type: !37, isLocal: false, isDefinition: true, scopeLine: 77, isOptimized: false, variables: !2)
!37 = !DISubroutineType(types: !38)
!38 = !{!11, !11}
!39 = !{i32 2, !"Dwarf Version", i32 4}
!40 = !{i32 2, !"Debug Info Version", i32 3}
!41 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!42 = !DILocalVariable(name: "dest", arg: 1, scope: !25, file: !1, line: 23, type: !4)
!43 = !DIExpression()
!44 = !DILocation(line: 23, column: 12, scope: !25)
!45 = !DILocalVariable(name: "destLen", arg: 2, scope: !25, file: !1, line: 24, type: !29)
!46 = !DILocation(line: 24, column: 13, scope: !25)
!47 = !DILocalVariable(name: "source", arg: 3, scope: !25, file: !1, line: 25, type: !31)
!48 = !DILocation(line: 25, column: 18, scope: !25)
!49 = !DILocalVariable(name: "sourceLen", arg: 4, scope: !25, file: !1, line: 26, type: !11)
!50 = !DILocation(line: 26, column: 11, scope: !25)
!51 = !DILocalVariable(name: "level", arg: 5, scope: !25, file: !1, line: 27, type: !28)
!52 = !DILocation(line: 27, column: 9, scope: !25)
!53 = !DILocalVariable(name: "stream", scope: !25, file: !1, line: 29, type: !54)
!54 = !DIDerivedType(tag: DW_TAG_typedef, name: "z_stream", file: !14, line: 101, baseType: !55)
!55 = !DICompositeType(tag: DW_TAG_structure_type, name: "z_stream_s", file: !14, line: 82, size: 896, align: 64, elements: !56)
!56 = !{!57, !58, !59, !60, !61, !62, !63, !66, !71, !72, !73, !74, !75, !76}
!57 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !55, file: !14, line: 83, baseType: !4, size: 64, align: 64)
!58 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !55, file: !14, line: 84, baseType: !9, size: 32, align: 32, offset: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "total_in", scope: !55, file: !14, line: 85, baseType: !11, size: 64, align: 64, offset: 128)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !55, file: !14, line: 87, baseType: !4, size: 64, align: 64, offset: 192)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !55, file: !14, line: 88, baseType: !9, size: 32, align: 32, offset: 256)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "total_out", scope: !55, file: !14, line: 89, baseType: !11, size: 64, align: 64, offset: 320)
!63 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !55, file: !14, line: 91, baseType: !64, size: 64, align: 64, offset: 384)
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !65, size: 64, align: 64)
!65 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !55, file: !14, line: 92, baseType: !67, size: 64, align: 64, offset: 448)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DICompositeType(tag: DW_TAG_structure_type, name: "internal_state", file: !14, line: 1346, size: 32, align: 32, elements: !69)
!69 = !{!70}
!70 = !DIDerivedType(tag: DW_TAG_member, name: "dummy", scope: !68, file: !14, line: 1346, baseType: !28, size: 32, align: 32)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "zalloc", scope: !55, file: !14, line: 94, baseType: !13, size: 64, align: 64, offset: 512)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "zfree", scope: !55, file: !14, line: 95, baseType: !20, size: 64, align: 64, offset: 576)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !55, file: !14, line: 96, baseType: !18, size: 64, align: 64, offset: 640)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "data_type", scope: !55, file: !14, line: 98, baseType: !28, size: 32, align: 32, offset: 704)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "adler", scope: !55, file: !14, line: 99, baseType: !11, size: 64, align: 64, offset: 768)
!76 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !55, file: !14, line: 100, baseType: !11, size: 64, align: 64, offset: 832)
!77 = !DILocation(line: 29, column: 14, scope: !25)
!78 = !DILocalVariable(name: "err", scope: !25, file: !1, line: 30, type: !28)
!79 = !DILocation(line: 30, column: 9, scope: !25)
!80 = !DILocation(line: 32, column: 30, scope: !25)
!81 = !DILocation(line: 32, column: 12, scope: !25)
!82 = !DILocation(line: 32, column: 20, scope: !25)
!83 = !DILocation(line: 33, column: 29, scope: !25)
!84 = !DILocation(line: 33, column: 23, scope: !25)
!85 = !DILocation(line: 33, column: 12, scope: !25)
!86 = !DILocation(line: 33, column: 21, scope: !25)
!87 = !DILocation(line: 38, column: 23, scope: !25)
!88 = !DILocation(line: 38, column: 12, scope: !25)
!89 = !DILocation(line: 38, column: 21, scope: !25)
!90 = !DILocation(line: 39, column: 31, scope: !25)
!91 = !DILocation(line: 39, column: 30, scope: !25)
!92 = !DILocation(line: 39, column: 24, scope: !25)
!93 = !DILocation(line: 39, column: 12, scope: !25)
!94 = !DILocation(line: 39, column: 22, scope: !25)
!95 = !DILocation(line: 40, column: 23, scope: !96)
!96 = distinct !DILexicalBlock(scope: !25, file: !1, line: 40, column: 9)
!97 = !DILocation(line: 40, column: 9, scope: !96)
!98 = !DILocation(line: 40, column: 37, scope: !96)
!99 = !DILocation(line: 40, column: 36, scope: !96)
!100 = !DILocation(line: 40, column: 33, scope: !96)
!101 = !DILocation(line: 40, column: 9, scope: !25)
!102 = !DILocation(line: 40, column: 46, scope: !103)
!103 = !DILexicalBlockFile(scope: !96, file: !1, discriminator: 1)
!104 = !DILocation(line: 42, column: 12, scope: !25)
!105 = !DILocation(line: 42, column: 19, scope: !25)
!106 = !DILocation(line: 43, column: 12, scope: !25)
!107 = !DILocation(line: 43, column: 18, scope: !25)
!108 = !DILocation(line: 44, column: 12, scope: !25)
!109 = !DILocation(line: 44, column: 19, scope: !25)
!110 = !DILocation(line: 46, column: 11, scope: !25)
!111 = !DILocation(line: 46, column: 9, scope: !25)
!112 = !DILocation(line: 47, column: 9, scope: !113)
!113 = distinct !DILexicalBlock(scope: !25, file: !1, line: 47, column: 9)
!114 = !DILocation(line: 47, column: 13, scope: !113)
!115 = !DILocation(line: 47, column: 9, scope: !25)
!116 = !DILocation(line: 47, column: 29, scope: !117)
!117 = !DILexicalBlockFile(scope: !113, file: !1, discriminator: 1)
!118 = !DILocation(line: 47, column: 22, scope: !117)
!119 = !DILocation(line: 49, column: 11, scope: !25)
!120 = !DILocation(line: 49, column: 9, scope: !25)
!121 = !DILocation(line: 50, column: 9, scope: !122)
!122 = distinct !DILexicalBlock(scope: !25, file: !1, line: 50, column: 9)
!123 = !DILocation(line: 50, column: 13, scope: !122)
!124 = !DILocation(line: 50, column: 9, scope: !25)
!125 = !DILocation(line: 51, column: 9, scope: !126)
!126 = distinct !DILexicalBlock(scope: !122, file: !1, line: 50, column: 30)
!127 = !DILocation(line: 52, column: 16, scope: !126)
!128 = !DILocation(line: 52, column: 20, scope: !126)
!129 = !DILocation(line: 52, column: 16, scope: !130)
!130 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 1)
!131 = !DILocation(line: 52, column: 44, scope: !132)
!132 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 2)
!133 = !DILocation(line: 52, column: 16, scope: !132)
!134 = !DILocation(line: 52, column: 16, scope: !135)
!135 = !DILexicalBlockFile(scope: !126, file: !1, discriminator: 3)
!136 = !DILocation(line: 52, column: 9, scope: !135)
!137 = !DILocation(line: 54, column: 23, scope: !25)
!138 = !DILocation(line: 54, column: 6, scope: !25)
!139 = !DILocation(line: 54, column: 14, scope: !25)
!140 = !DILocation(line: 56, column: 11, scope: !25)
!141 = !DILocation(line: 56, column: 9, scope: !25)
!142 = !DILocation(line: 57, column: 12, scope: !25)
!143 = !DILocation(line: 57, column: 5, scope: !25)
!144 = !DILocation(line: 58, column: 1, scope: !25)
!145 = !DILocalVariable(name: "dest", arg: 1, scope: !33, file: !1, line: 63, type: !4)
!146 = !DILocation(line: 63, column: 12, scope: !33)
!147 = !DILocalVariable(name: "destLen", arg: 2, scope: !33, file: !1, line: 64, type: !29)
!148 = !DILocation(line: 64, column: 13, scope: !33)
!149 = !DILocalVariable(name: "source", arg: 3, scope: !33, file: !1, line: 65, type: !31)
!150 = !DILocation(line: 65, column: 18, scope: !33)
!151 = !DILocalVariable(name: "sourceLen", arg: 4, scope: !33, file: !1, line: 66, type: !11)
!152 = !DILocation(line: 66, column: 11, scope: !33)
!153 = !DILocation(line: 68, column: 22, scope: !33)
!154 = !DILocation(line: 68, column: 28, scope: !33)
!155 = !DILocation(line: 68, column: 37, scope: !33)
!156 = !DILocation(line: 68, column: 45, scope: !33)
!157 = !DILocation(line: 68, column: 12, scope: !33)
!158 = !DILocation(line: 68, column: 5, scope: !33)
!159 = !DILocalVariable(name: "sourceLen", arg: 1, scope: !36, file: !1, line: 76, type: !11)
!160 = !DILocation(line: 76, column: 11, scope: !36)
!161 = !DILocation(line: 78, column: 12, scope: !36)
!162 = !DILocation(line: 78, column: 25, scope: !36)
!163 = !DILocation(line: 78, column: 35, scope: !36)
!164 = !DILocation(line: 78, column: 22, scope: !36)
!165 = !DILocation(line: 78, column: 45, scope: !36)
!166 = !DILocation(line: 78, column: 55, scope: !36)
!167 = !DILocation(line: 78, column: 42, scope: !36)
!168 = !DILocation(line: 78, column: 62, scope: !36)
!169 = !DILocation(line: 78, column: 5, scope: !36)
