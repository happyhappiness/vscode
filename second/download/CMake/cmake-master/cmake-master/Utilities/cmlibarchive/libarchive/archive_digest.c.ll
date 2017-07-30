; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_digest.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_digest = type { i32 (i8*)*, i32 (i8*, i8*, i64)*, i32 (i8*, i8*)*, i32 (i8*)*, i32 (i8*, i8*, i64)*, i32 (i8*, i8*)*, i32 (i8*)*, i32 (i8*, i8*, i64)*, i32 (i8*, i8*)*, i32 (i8*)*, i32 (i8*, i8*, i64)*, i32 (i8*, i8*)*, i32 (i8*)*, i32 (i8*, i8*, i64)*, i32 (i8*, i8*)*, i32 (i8*)*, i32 (i8*, i8*, i64)*, i32 (i8*, i8*)* }

@__archive_digest = constant %struct.archive_digest { i32 (i8*)* @__archive_stub_md5init, i32 (i8*, i8*, i64)* @__archive_stub_md5update, i32 (i8*, i8*)* @__archive_stub_md5final, i32 (i8*)* @__archive_stub_ripemd160init, i32 (i8*, i8*, i64)* @__archive_stub_ripemd160update, i32 (i8*, i8*)* @__archive_stub_ripemd160final, i32 (i8*)* @__archive_stub_sha1init, i32 (i8*, i8*, i64)* @__archive_stub_sha1update, i32 (i8*, i8*)* @__archive_stub_sha1final, i32 (i8*)* @__archive_stub_sha256init, i32 (i8*, i8*, i64)* @__archive_stub_sha256update, i32 (i8*, i8*)* @__archive_stub_sha256final, i32 (i8*)* @__archive_stub_sha384init, i32 (i8*, i8*, i64)* @__archive_stub_sha384update, i32 (i8*, i8*)* @__archive_stub_sha384final, i32 (i8*)* @__archive_stub_sha512init, i32 (i8*, i8*, i64)* @__archive_stub_sha512update, i32 (i8*, i8*)* @__archive_stub_sha512final }, align 8

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_md5init(i8* %ctx) #0 !dbg !4 {
entry:
  %ctx.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !123, metadata !124), !dbg !125
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !126
  ret i32 -25, !dbg !127
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_md5update(i8* %ctx, i8* %indata, i64 %insize) #0 !dbg !12 {
entry:
  %ctx.addr = alloca i8*, align 8
  %indata.addr = alloca i8*, align 8
  %insize.addr = alloca i64, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !128, metadata !124), !dbg !129
  store i8* %indata, i8** %indata.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %indata.addr, metadata !130, metadata !124), !dbg !131
  store i64 %insize, i64* %insize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %insize.addr, metadata !132, metadata !124), !dbg !133
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !134
  %1 = load i8*, i8** %indata.addr, align 8, !dbg !135
  %2 = load i64, i64* %insize.addr, align 8, !dbg !136
  ret i32 -25, !dbg !137
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_md5final(i8* %ctx, i8* %md) #0 !dbg !20 {
entry:
  %ctx.addr = alloca i8*, align 8
  %md.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !138, metadata !124), !dbg !139
  store i8* %md, i8** %md.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %md.addr, metadata !140, metadata !124), !dbg !141
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !142
  %1 = load i8*, i8** %md.addr, align 8, !dbg !143
  ret i32 -25, !dbg !144
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_ripemd160init(i8* %ctx) #0 !dbg !24 {
entry:
  %ctx.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !145, metadata !124), !dbg !146
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !147
  ret i32 -25, !dbg !148
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_ripemd160update(i8* %ctx, i8* %indata, i64 %insize) #0 !dbg !29 {
entry:
  %ctx.addr = alloca i8*, align 8
  %indata.addr = alloca i8*, align 8
  %insize.addr = alloca i64, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !149, metadata !124), !dbg !150
  store i8* %indata, i8** %indata.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %indata.addr, metadata !151, metadata !124), !dbg !152
  store i64 %insize, i64* %insize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %insize.addr, metadata !153, metadata !124), !dbg !154
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !155
  %1 = load i8*, i8** %indata.addr, align 8, !dbg !156
  %2 = load i64, i64* %insize.addr, align 8, !dbg !157
  ret i32 -25, !dbg !158
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_ripemd160final(i8* %ctx, i8* %md) #0 !dbg !32 {
entry:
  %ctx.addr = alloca i8*, align 8
  %md.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !159, metadata !124), !dbg !160
  store i8* %md, i8** %md.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %md.addr, metadata !161, metadata !124), !dbg !162
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !163
  %1 = load i8*, i8** %md.addr, align 8, !dbg !164
  ret i32 -25, !dbg !165
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha1init(i8* %ctx) #0 !dbg !35 {
entry:
  %ctx.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !166, metadata !124), !dbg !167
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !168
  ret i32 -25, !dbg !169
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha1update(i8* %ctx, i8* %indata, i64 %insize) #0 !dbg !40 {
entry:
  %ctx.addr = alloca i8*, align 8
  %indata.addr = alloca i8*, align 8
  %insize.addr = alloca i64, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !170, metadata !124), !dbg !171
  store i8* %indata, i8** %indata.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %indata.addr, metadata !172, metadata !124), !dbg !173
  store i64 %insize, i64* %insize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %insize.addr, metadata !174, metadata !124), !dbg !175
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !176
  %1 = load i8*, i8** %indata.addr, align 8, !dbg !177
  %2 = load i64, i64* %insize.addr, align 8, !dbg !178
  ret i32 -25, !dbg !179
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha1final(i8* %ctx, i8* %md) #0 !dbg !43 {
entry:
  %ctx.addr = alloca i8*, align 8
  %md.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !180, metadata !124), !dbg !181
  store i8* %md, i8** %md.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %md.addr, metadata !182, metadata !124), !dbg !183
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !184
  %1 = load i8*, i8** %md.addr, align 8, !dbg !185
  ret i32 -25, !dbg !186
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha256init(i8* %ctx) #0 !dbg !46 {
entry:
  %ctx.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !187, metadata !124), !dbg !188
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !189
  ret i32 -25, !dbg !190
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha256update(i8* %ctx, i8* %indata, i64 %insize) #0 !dbg !51 {
entry:
  %ctx.addr = alloca i8*, align 8
  %indata.addr = alloca i8*, align 8
  %insize.addr = alloca i64, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !191, metadata !124), !dbg !192
  store i8* %indata, i8** %indata.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %indata.addr, metadata !193, metadata !124), !dbg !194
  store i64 %insize, i64* %insize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %insize.addr, metadata !195, metadata !124), !dbg !196
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !197
  %1 = load i8*, i8** %indata.addr, align 8, !dbg !198
  %2 = load i64, i64* %insize.addr, align 8, !dbg !199
  ret i32 -25, !dbg !200
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha256final(i8* %ctx, i8* %md) #0 !dbg !54 {
entry:
  %ctx.addr = alloca i8*, align 8
  %md.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !201, metadata !124), !dbg !202
  store i8* %md, i8** %md.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %md.addr, metadata !203, metadata !124), !dbg !204
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !205
  %1 = load i8*, i8** %md.addr, align 8, !dbg !206
  ret i32 -25, !dbg !207
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha384init(i8* %ctx) #0 !dbg !57 {
entry:
  %ctx.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !208, metadata !124), !dbg !209
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !210
  ret i32 -25, !dbg !211
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha384update(i8* %ctx, i8* %indata, i64 %insize) #0 !dbg !62 {
entry:
  %ctx.addr = alloca i8*, align 8
  %indata.addr = alloca i8*, align 8
  %insize.addr = alloca i64, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !212, metadata !124), !dbg !213
  store i8* %indata, i8** %indata.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %indata.addr, metadata !214, metadata !124), !dbg !215
  store i64 %insize, i64* %insize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %insize.addr, metadata !216, metadata !124), !dbg !217
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !218
  %1 = load i8*, i8** %indata.addr, align 8, !dbg !219
  %2 = load i64, i64* %insize.addr, align 8, !dbg !220
  ret i32 -25, !dbg !221
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha384final(i8* %ctx, i8* %md) #0 !dbg !65 {
entry:
  %ctx.addr = alloca i8*, align 8
  %md.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !222, metadata !124), !dbg !223
  store i8* %md, i8** %md.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %md.addr, metadata !224, metadata !124), !dbg !225
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !226
  %1 = load i8*, i8** %md.addr, align 8, !dbg !227
  ret i32 -25, !dbg !228
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha512init(i8* %ctx) #0 !dbg !68 {
entry:
  %ctx.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !229, metadata !124), !dbg !230
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !231
  ret i32 -25, !dbg !232
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha512update(i8* %ctx, i8* %indata, i64 %insize) #0 !dbg !73 {
entry:
  %ctx.addr = alloca i8*, align 8
  %indata.addr = alloca i8*, align 8
  %insize.addr = alloca i64, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !233, metadata !124), !dbg !234
  store i8* %indata, i8** %indata.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %indata.addr, metadata !235, metadata !124), !dbg !236
  store i64 %insize, i64* %insize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %insize.addr, metadata !237, metadata !124), !dbg !238
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !239
  %1 = load i8*, i8** %indata.addr, align 8, !dbg !240
  %2 = load i64, i64* %insize.addr, align 8, !dbg !241
  ret i32 -25, !dbg !242
}

; Function Attrs: nounwind uwtable
define internal i32 @__archive_stub_sha512final(i8* %ctx, i8* %md) #0 !dbg !76 {
entry:
  %ctx.addr = alloca i8*, align 8
  %md.addr = alloca i8*, align 8
  store i8* %ctx, i8** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ctx.addr, metadata !243, metadata !124), !dbg !244
  store i8* %md, i8** %md.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %md.addr, metadata !245, metadata !124), !dbg !246
  %0 = load i8*, i8** %ctx.addr, align 8, !dbg !247
  %1 = load i8*, i8** %md.addr, align 8, !dbg !248
  ret i32 -25, !dbg !249
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!120, !121}
!llvm.ident = !{!122}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !79)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_digest.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !12, !20, !24, !29, !32, !35, !40, !43, !46, !51, !54, !57, !62, !65, !68, !73, !76}
!4 = distinct !DISubprogram(name: "__archive_stub_md5init", scope: !1, file: !1, line: 263, type: !5, isLocal: true, isDefinition: true, scopeLine: 264, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7, !8}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_md5_ctx", file: !10, line: 169, baseType: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_digest_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!12 = distinct !DISubprogram(name: "__archive_stub_md5update", scope: !1, file: !1, line: 270, type: !13, isLocal: true, isDefinition: true, scopeLine: 272, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!13 = !DISubroutineType(types: !14)
!14 = !{!7, !8, !15, !17}
!15 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!16 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!17 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !18, line: 62, baseType: !19)
!18 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!19 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!20 = distinct !DISubprogram(name: "__archive_stub_md5final", scope: !1, file: !1, line: 280, type: !21, isLocal: true, isDefinition: true, scopeLine: 281, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!21 = !DISubroutineType(types: !22)
!22 = !{!7, !8, !23}
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!24 = distinct !DISubprogram(name: "__archive_stub_ripemd160init", scope: !1, file: !1, line: 395, type: !25, isLocal: true, isDefinition: true, scopeLine: 396, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!25 = !DISubroutineType(types: !26)
!26 = !{!7, !27}
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_rmd160_ctx", file: !10, line: 181, baseType: !11)
!29 = distinct !DISubprogram(name: "__archive_stub_ripemd160update", scope: !1, file: !1, line: 402, type: !30, isLocal: true, isDefinition: true, scopeLine: 404, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!30 = !DISubroutineType(types: !31)
!31 = !{!7, !27, !15, !17}
!32 = distinct !DISubprogram(name: "__archive_stub_ripemd160final", scope: !1, file: !1, line: 412, type: !33, isLocal: true, isDefinition: true, scopeLine: 413, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!33 = !DISubroutineType(types: !34)
!34 = !{!7, !27, !23}
!35 = distinct !DISubprogram(name: "__archive_stub_sha1init", scope: !1, file: !1, line: 576, type: !36, isLocal: true, isDefinition: true, scopeLine: 577, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!36 = !DISubroutineType(types: !37)
!37 = !{!7, !38}
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_sha1_ctx", file: !10, line: 197, baseType: !11)
!40 = distinct !DISubprogram(name: "__archive_stub_sha1update", scope: !1, file: !1, line: 583, type: !41, isLocal: true, isDefinition: true, scopeLine: 585, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!41 = !DISubroutineType(types: !42)
!42 = !{!7, !38, !15, !17}
!43 = distinct !DISubprogram(name: "__archive_stub_sha1final", scope: !1, file: !1, line: 593, type: !44, isLocal: true, isDefinition: true, scopeLine: 594, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!44 = !DISubroutineType(types: !45)
!45 = !{!7, !38, !23}
!46 = distinct !DISubprogram(name: "__archive_stub_sha256init", scope: !1, file: !1, line: 801, type: !47, isLocal: true, isDefinition: true, scopeLine: 802, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!47 = !DISubroutineType(types: !48)
!48 = !{!7, !49}
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_sha256_ctx", file: !10, line: 217, baseType: !11)
!51 = distinct !DISubprogram(name: "__archive_stub_sha256update", scope: !1, file: !1, line: 808, type: !52, isLocal: true, isDefinition: true, scopeLine: 810, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!52 = !DISubroutineType(types: !53)
!53 = !{!7, !49, !15, !17}
!54 = distinct !DISubprogram(name: "__archive_stub_sha256final", scope: !1, file: !1, line: 818, type: !55, isLocal: true, isDefinition: true, scopeLine: 819, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!55 = !DISubroutineType(types: !56)
!56 = !{!7, !49, !23}
!57 = distinct !DISubprogram(name: "__archive_stub_sha384init", scope: !1, file: !1, line: 1002, type: !58, isLocal: true, isDefinition: true, scopeLine: 1003, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!58 = !DISubroutineType(types: !59)
!59 = !{!7, !60}
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_sha384_ctx", file: !10, line: 235, baseType: !11)
!62 = distinct !DISubprogram(name: "__archive_stub_sha384update", scope: !1, file: !1, line: 1009, type: !63, isLocal: true, isDefinition: true, scopeLine: 1011, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!63 = !DISubroutineType(types: !64)
!64 = !{!7, !60, !15, !17}
!65 = distinct !DISubprogram(name: "__archive_stub_sha384final", scope: !1, file: !1, line: 1019, type: !66, isLocal: true, isDefinition: true, scopeLine: 1020, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!66 = !DISubroutineType(types: !67)
!67 = !{!7, !60, !23}
!68 = distinct !DISubprogram(name: "__archive_stub_sha512init", scope: !1, file: !1, line: 1227, type: !69, isLocal: true, isDefinition: true, scopeLine: 1228, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!69 = !DISubroutineType(types: !70)
!70 = !{!7, !71}
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !72, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_sha512_ctx", file: !10, line: 255, baseType: !11)
!73 = distinct !DISubprogram(name: "__archive_stub_sha512update", scope: !1, file: !1, line: 1234, type: !74, isLocal: true, isDefinition: true, scopeLine: 1236, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!74 = !DISubroutineType(types: !75)
!75 = !{!7, !71, !15, !17}
!76 = distinct !DISubprogram(name: "__archive_stub_sha512final", scope: !1, file: !1, line: 1244, type: !77, isLocal: true, isDefinition: true, scopeLine: 1245, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!77 = !DISubroutineType(types: !78)
!78 = !{!7, !71, !23}
!79 = !{!80}
!80 = !DIGlobalVariable(name: "__archive_digest", scope: !0, file: !1, line: 1264, type: !81, isLocal: false, isDefinition: true, variable: %struct.archive_digest* @__archive_digest)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_digest", file: !10, line: 352, size: 1152, align: 64, elements: !83)
!83 = !{!84, !86, !88, !90, !92, !94, !96, !98, !100, !102, !104, !106, !108, !110, !112, !114, !116, !118}
!84 = !DIDerivedType(tag: DW_TAG_member, name: "md5init", scope: !82, file: !10, line: 355, baseType: !85, size: 64, align: 64)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "md5update", scope: !82, file: !10, line: 356, baseType: !87, size: 64, align: 64, offset: 64)
!87 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !13, size: 64, align: 64)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "md5final", scope: !82, file: !10, line: 357, baseType: !89, size: 64, align: 64, offset: 128)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "rmd160init", scope: !82, file: !10, line: 358, baseType: !91, size: 64, align: 64, offset: 192)
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "rmd160update", scope: !82, file: !10, line: 359, baseType: !93, size: 64, align: 64, offset: 256)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "rmd160final", scope: !82, file: !10, line: 360, baseType: !95, size: 64, align: 64, offset: 320)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "sha1init", scope: !82, file: !10, line: 361, baseType: !97, size: 64, align: 64, offset: 384)
!97 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "sha1update", scope: !82, file: !10, line: 362, baseType: !99, size: 64, align: 64, offset: 448)
!99 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "sha1final", scope: !82, file: !10, line: 363, baseType: !101, size: 64, align: 64, offset: 512)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "sha256init", scope: !82, file: !10, line: 364, baseType: !103, size: 64, align: 64, offset: 576)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "sha256update", scope: !82, file: !10, line: 365, baseType: !105, size: 64, align: 64, offset: 640)
!105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "sha256final", scope: !82, file: !10, line: 366, baseType: !107, size: 64, align: 64, offset: 704)
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "sha384init", scope: !82, file: !10, line: 367, baseType: !109, size: 64, align: 64, offset: 768)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "sha384update", scope: !82, file: !10, line: 368, baseType: !111, size: 64, align: 64, offset: 832)
!111 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "sha384final", scope: !82, file: !10, line: 369, baseType: !113, size: 64, align: 64, offset: 896)
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !66, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "sha512init", scope: !82, file: !10, line: 370, baseType: !115, size: 64, align: 64, offset: 960)
!115 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !69, size: 64, align: 64)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "sha512update", scope: !82, file: !10, line: 371, baseType: !117, size: 64, align: 64, offset: 1024)
!117 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "sha512final", scope: !82, file: !10, line: 372, baseType: !119, size: 64, align: 64, offset: 1088)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!120 = !{i32 2, !"Dwarf Version", i32 4}
!121 = !{i32 2, !"Debug Info Version", i32 3}
!122 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!123 = !DILocalVariable(name: "ctx", arg: 1, scope: !4, file: !1, line: 263, type: !8)
!124 = !DIExpression()
!125 = !DILocation(line: 263, column: 41, scope: !4)
!126 = !DILocation(line: 265, column: 8, scope: !4)
!127 = !DILocation(line: 266, column: 2, scope: !4)
!128 = !DILocalVariable(name: "ctx", arg: 1, scope: !12, file: !1, line: 270, type: !8)
!129 = !DILocation(line: 270, column: 43, scope: !12)
!130 = !DILocalVariable(name: "indata", arg: 2, scope: !12, file: !1, line: 270, type: !15)
!131 = !DILocation(line: 270, column: 60, scope: !12)
!132 = !DILocalVariable(name: "insize", arg: 3, scope: !12, file: !1, line: 271, type: !17)
!133 = !DILocation(line: 271, column: 12, scope: !12)
!134 = !DILocation(line: 273, column: 8, scope: !12)
!135 = !DILocation(line: 274, column: 8, scope: !12)
!136 = !DILocation(line: 275, column: 8, scope: !12)
!137 = !DILocation(line: 276, column: 2, scope: !12)
!138 = !DILocalVariable(name: "ctx", arg: 1, scope: !20, file: !1, line: 280, type: !8)
!139 = !DILocation(line: 280, column: 42, scope: !20)
!140 = !DILocalVariable(name: "md", arg: 2, scope: !20, file: !1, line: 280, type: !23)
!141 = !DILocation(line: 280, column: 53, scope: !20)
!142 = !DILocation(line: 282, column: 8, scope: !20)
!143 = !DILocation(line: 283, column: 8, scope: !20)
!144 = !DILocation(line: 284, column: 2, scope: !20)
!145 = !DILocalVariable(name: "ctx", arg: 1, scope: !24, file: !1, line: 395, type: !27)
!146 = !DILocation(line: 395, column: 50, scope: !24)
!147 = !DILocation(line: 397, column: 8, scope: !24)
!148 = !DILocation(line: 398, column: 2, scope: !24)
!149 = !DILocalVariable(name: "ctx", arg: 1, scope: !29, file: !1, line: 402, type: !27)
!150 = !DILocation(line: 402, column: 52, scope: !29)
!151 = !DILocalVariable(name: "indata", arg: 2, scope: !29, file: !1, line: 402, type: !15)
!152 = !DILocation(line: 402, column: 69, scope: !29)
!153 = !DILocalVariable(name: "insize", arg: 3, scope: !29, file: !1, line: 403, type: !17)
!154 = !DILocation(line: 403, column: 12, scope: !29)
!155 = !DILocation(line: 405, column: 8, scope: !29)
!156 = !DILocation(line: 406, column: 8, scope: !29)
!157 = !DILocation(line: 407, column: 8, scope: !29)
!158 = !DILocation(line: 408, column: 2, scope: !29)
!159 = !DILocalVariable(name: "ctx", arg: 1, scope: !32, file: !1, line: 412, type: !27)
!160 = !DILocation(line: 412, column: 51, scope: !32)
!161 = !DILocalVariable(name: "md", arg: 2, scope: !32, file: !1, line: 412, type: !23)
!162 = !DILocation(line: 412, column: 62, scope: !32)
!163 = !DILocation(line: 414, column: 8, scope: !32)
!164 = !DILocation(line: 415, column: 8, scope: !32)
!165 = !DILocation(line: 416, column: 2, scope: !32)
!166 = !DILocalVariable(name: "ctx", arg: 1, scope: !35, file: !1, line: 576, type: !38)
!167 = !DILocation(line: 576, column: 43, scope: !35)
!168 = !DILocation(line: 578, column: 8, scope: !35)
!169 = !DILocation(line: 579, column: 2, scope: !35)
!170 = !DILocalVariable(name: "ctx", arg: 1, scope: !40, file: !1, line: 583, type: !38)
!171 = !DILocation(line: 583, column: 45, scope: !40)
!172 = !DILocalVariable(name: "indata", arg: 2, scope: !40, file: !1, line: 583, type: !15)
!173 = !DILocation(line: 583, column: 62, scope: !40)
!174 = !DILocalVariable(name: "insize", arg: 3, scope: !40, file: !1, line: 584, type: !17)
!175 = !DILocation(line: 584, column: 12, scope: !40)
!176 = !DILocation(line: 586, column: 8, scope: !40)
!177 = !DILocation(line: 587, column: 8, scope: !40)
!178 = !DILocation(line: 588, column: 8, scope: !40)
!179 = !DILocation(line: 589, column: 2, scope: !40)
!180 = !DILocalVariable(name: "ctx", arg: 1, scope: !43, file: !1, line: 593, type: !38)
!181 = !DILocation(line: 593, column: 44, scope: !43)
!182 = !DILocalVariable(name: "md", arg: 2, scope: !43, file: !1, line: 593, type: !23)
!183 = !DILocation(line: 593, column: 55, scope: !43)
!184 = !DILocation(line: 595, column: 8, scope: !43)
!185 = !DILocation(line: 596, column: 8, scope: !43)
!186 = !DILocation(line: 597, column: 2, scope: !43)
!187 = !DILocalVariable(name: "ctx", arg: 1, scope: !46, file: !1, line: 801, type: !49)
!188 = !DILocation(line: 801, column: 47, scope: !46)
!189 = !DILocation(line: 803, column: 8, scope: !46)
!190 = !DILocation(line: 804, column: 2, scope: !46)
!191 = !DILocalVariable(name: "ctx", arg: 1, scope: !51, file: !1, line: 808, type: !49)
!192 = !DILocation(line: 808, column: 49, scope: !51)
!193 = !DILocalVariable(name: "indata", arg: 2, scope: !51, file: !1, line: 808, type: !15)
!194 = !DILocation(line: 808, column: 66, scope: !51)
!195 = !DILocalVariable(name: "insize", arg: 3, scope: !51, file: !1, line: 809, type: !17)
!196 = !DILocation(line: 809, column: 12, scope: !51)
!197 = !DILocation(line: 811, column: 8, scope: !51)
!198 = !DILocation(line: 812, column: 8, scope: !51)
!199 = !DILocation(line: 813, column: 8, scope: !51)
!200 = !DILocation(line: 814, column: 2, scope: !51)
!201 = !DILocalVariable(name: "ctx", arg: 1, scope: !54, file: !1, line: 818, type: !49)
!202 = !DILocation(line: 818, column: 48, scope: !54)
!203 = !DILocalVariable(name: "md", arg: 2, scope: !54, file: !1, line: 818, type: !23)
!204 = !DILocation(line: 818, column: 59, scope: !54)
!205 = !DILocation(line: 820, column: 8, scope: !54)
!206 = !DILocation(line: 821, column: 8, scope: !54)
!207 = !DILocation(line: 822, column: 2, scope: !54)
!208 = !DILocalVariable(name: "ctx", arg: 1, scope: !57, file: !1, line: 1002, type: !60)
!209 = !DILocation(line: 1002, column: 47, scope: !57)
!210 = !DILocation(line: 1004, column: 8, scope: !57)
!211 = !DILocation(line: 1005, column: 2, scope: !57)
!212 = !DILocalVariable(name: "ctx", arg: 1, scope: !62, file: !1, line: 1009, type: !60)
!213 = !DILocation(line: 1009, column: 49, scope: !62)
!214 = !DILocalVariable(name: "indata", arg: 2, scope: !62, file: !1, line: 1009, type: !15)
!215 = !DILocation(line: 1009, column: 66, scope: !62)
!216 = !DILocalVariable(name: "insize", arg: 3, scope: !62, file: !1, line: 1010, type: !17)
!217 = !DILocation(line: 1010, column: 12, scope: !62)
!218 = !DILocation(line: 1012, column: 8, scope: !62)
!219 = !DILocation(line: 1013, column: 8, scope: !62)
!220 = !DILocation(line: 1014, column: 8, scope: !62)
!221 = !DILocation(line: 1015, column: 2, scope: !62)
!222 = !DILocalVariable(name: "ctx", arg: 1, scope: !65, file: !1, line: 1019, type: !60)
!223 = !DILocation(line: 1019, column: 48, scope: !65)
!224 = !DILocalVariable(name: "md", arg: 2, scope: !65, file: !1, line: 1019, type: !23)
!225 = !DILocation(line: 1019, column: 59, scope: !65)
!226 = !DILocation(line: 1021, column: 8, scope: !65)
!227 = !DILocation(line: 1022, column: 8, scope: !65)
!228 = !DILocation(line: 1023, column: 2, scope: !65)
!229 = !DILocalVariable(name: "ctx", arg: 1, scope: !68, file: !1, line: 1227, type: !71)
!230 = !DILocation(line: 1227, column: 47, scope: !68)
!231 = !DILocation(line: 1229, column: 8, scope: !68)
!232 = !DILocation(line: 1230, column: 2, scope: !68)
!233 = !DILocalVariable(name: "ctx", arg: 1, scope: !73, file: !1, line: 1234, type: !71)
!234 = !DILocation(line: 1234, column: 49, scope: !73)
!235 = !DILocalVariable(name: "indata", arg: 2, scope: !73, file: !1, line: 1234, type: !15)
!236 = !DILocation(line: 1234, column: 66, scope: !73)
!237 = !DILocalVariable(name: "insize", arg: 3, scope: !73, file: !1, line: 1235, type: !17)
!238 = !DILocation(line: 1235, column: 12, scope: !73)
!239 = !DILocation(line: 1237, column: 8, scope: !73)
!240 = !DILocation(line: 1238, column: 8, scope: !73)
!241 = !DILocation(line: 1239, column: 8, scope: !73)
!242 = !DILocation(line: 1240, column: 2, scope: !73)
!243 = !DILocalVariable(name: "ctx", arg: 1, scope: !76, file: !1, line: 1244, type: !71)
!244 = !DILocation(line: 1244, column: 48, scope: !76)
!245 = !DILocalVariable(name: "md", arg: 2, scope: !76, file: !1, line: 1244, type: !23)
!246 = !DILocation(line: 1244, column: 59, scope: !76)
!247 = !DILocation(line: 1246, column: 8, scope: !76)
!248 = !DILocation(line: 1247, column: 8, scope: !76)
!249 = !DILocation(line: 1248, column: 2, scope: !76)
