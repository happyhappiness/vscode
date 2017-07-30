; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_hmac.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_hmac = type { i32 (i32*, i8*, i64)*, void (i32*, i8*, i64)*, void (i32*, i8*, i64*)*, void (i32*)* }

@__archive_hmac = constant %struct.archive_hmac { i32 (i32*, i8*, i64)* @__hmac_sha1_init, void (i32*, i8*, i64)* @__hmac_sha1_update, void (i32*, i8*, i64*)* @__hmac_sha1_final, void (i32*)* @__hmac_sha1_cleanup }, align 8

; Function Attrs: nounwind uwtable
define i32 @__libarchive_hmac_build_hack() #0 !dbg !4 {
entry:
  ret i32 0, !dbg !49
}

; Function Attrs: nounwind uwtable
define internal i32 @__hmac_sha1_init(i32* %ctx, i8* %key, i64 %key_len) #0 !dbg !8 {
entry:
  %ctx.addr = alloca i32*, align 8
  %key.addr = alloca i8*, align 8
  %key_len.addr = alloca i64, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !50, metadata !51), !dbg !52
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !53, metadata !51), !dbg !54
  store i64 %key_len, i64* %key_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key_len.addr, metadata !55, metadata !51), !dbg !56
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !57
  %1 = load i8*, i8** %key.addr, align 8, !dbg !58
  %2 = load i64, i64* %key_len.addr, align 8, !dbg !59
  ret i32 -1, !dbg !60
}

; Function Attrs: nounwind uwtable
define internal void @__hmac_sha1_update(i32* %ctx, i8* %data, i64 %data_len) #0 !dbg !22 {
entry:
  %ctx.addr = alloca i32*, align 8
  %data.addr = alloca i8*, align 8
  %data_len.addr = alloca i64, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !61, metadata !51), !dbg !62
  store i8* %data, i8** %data.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %data.addr, metadata !63, metadata !51), !dbg !64
  store i64 %data_len, i64* %data_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %data_len.addr, metadata !65, metadata !51), !dbg !66
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !67
  %1 = load i8*, i8** %data.addr, align 8, !dbg !68
  %2 = load i64, i64* %data_len.addr, align 8, !dbg !69
  ret void, !dbg !70
}

; Function Attrs: nounwind uwtable
define internal void @__hmac_sha1_final(i32* %ctx, i8* %out, i64* %out_len) #0 !dbg !25 {
entry:
  %ctx.addr = alloca i32*, align 8
  %out.addr = alloca i8*, align 8
  %out_len.addr = alloca i64*, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !71, metadata !51), !dbg !72
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !73, metadata !51), !dbg !74
  store i64* %out_len, i64** %out_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_len.addr, metadata !75, metadata !51), !dbg !76
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !77
  %1 = load i8*, i8** %out.addr, align 8, !dbg !78
  %2 = load i64*, i64** %out_len.addr, align 8, !dbg !79
  ret void, !dbg !80
}

; Function Attrs: nounwind uwtable
define internal void @__hmac_sha1_cleanup(i32* %ctx) #0 !dbg !30 {
entry:
  %ctx.addr = alloca i32*, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !81, metadata !51), !dbg !82
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !83
  ret void, !dbg !84
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!46, !47}
!llvm.ident = !{!48}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !33)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_hmac.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !8, !22, !25, !30}
!4 = distinct !DISubprogram(name: "__libarchive_hmac_build_hack", scope: !1, file: !1, line: 43, type: !5, isLocal: false, isDefinition: true, scopeLine: 43, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = distinct !DISubprogram(name: "__hmac_sha1_init", scope: !1, file: !1, line: 216, type: !9, isLocal: true, isDefinition: true, scopeLine: 217, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = !DISubroutineType(types: !10)
!10 = !{!7, !11, !14, !19}
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_hmac_sha1_ctx", file: !13, line: 79, baseType: !7)
!13 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_hmac_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!14 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !15, size: 64, align: 64)
!15 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !16)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !17, line: 48, baseType: !18)
!17 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!18 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !20, line: 62, baseType: !21)
!20 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!21 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!22 = distinct !DISubprogram(name: "__hmac_sha1_update", scope: !1, file: !1, line: 225, type: !23, isLocal: true, isDefinition: true, scopeLine: 227, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!23 = !DISubroutineType(types: !24)
!24 = !{null, !11, !14, !19}
!25 = distinct !DISubprogram(name: "__hmac_sha1_final", scope: !1, file: !1, line: 234, type: !26, isLocal: true, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!26 = !DISubroutineType(types: !27)
!27 = !{null, !11, !28, !29}
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!30 = distinct !DISubprogram(name: "__hmac_sha1_cleanup", scope: !1, file: !1, line: 242, type: !31, isLocal: true, isDefinition: true, scopeLine: 243, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = !DISubroutineType(types: !32)
!32 = !{null, !11}
!33 = !{!34}
!34 = !DIGlobalVariable(name: "__archive_hmac", scope: !0, file: !1, line: 249, type: !35, isLocal: false, isDefinition: true, variable: %struct.archive_hmac* @__archive_hmac)
!35 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !36)
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_hmac", file: !13, line: 95, size: 256, align: 64, elements: !37)
!37 = !{!38, !40, !42, !44}
!38 = !DIDerivedType(tag: DW_TAG_member, name: "__hmac_sha1_init", scope: !36, file: !13, line: 97, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "__hmac_sha1_update", scope: !36, file: !13, line: 99, baseType: !41, size: 64, align: 64, offset: 64)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "__hmac_sha1_final", scope: !36, file: !13, line: 101, baseType: !43, size: 64, align: 64, offset: 128)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "__hmac_sha1_cleanup", scope: !36, file: !13, line: 102, baseType: !45, size: 64, align: 64, offset: 192)
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!46 = !{i32 2, !"Dwarf Version", i32 4}
!47 = !{i32 2, !"Debug Info Version", i32 3}
!48 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!49 = !DILocation(line: 44, column: 2, scope: !4)
!50 = !DILocalVariable(name: "ctx", arg: 1, scope: !8, file: !1, line: 216, type: !11)
!51 = !DIExpression()
!52 = !DILocation(line: 216, column: 41, scope: !8)
!53 = !DILocalVariable(name: "key", arg: 2, scope: !8, file: !1, line: 216, type: !14)
!54 = !DILocation(line: 216, column: 61, scope: !8)
!55 = !DILocalVariable(name: "key_len", arg: 3, scope: !8, file: !1, line: 216, type: !19)
!56 = !DILocation(line: 216, column: 73, scope: !8)
!57 = !DILocation(line: 218, column: 8, scope: !8)
!58 = !DILocation(line: 219, column: 8, scope: !8)
!59 = !DILocation(line: 220, column: 8, scope: !8)
!60 = !DILocation(line: 221, column: 2, scope: !8)
!61 = !DILocalVariable(name: "ctx", arg: 1, scope: !22, file: !1, line: 225, type: !11)
!62 = !DILocation(line: 225, column: 43, scope: !22)
!63 = !DILocalVariable(name: "data", arg: 2, scope: !22, file: !1, line: 225, type: !14)
!64 = !DILocation(line: 225, column: 63, scope: !22)
!65 = !DILocalVariable(name: "data_len", arg: 3, scope: !22, file: !1, line: 226, type: !19)
!66 = !DILocation(line: 226, column: 12, scope: !22)
!67 = !DILocation(line: 228, column: 8, scope: !22)
!68 = !DILocation(line: 229, column: 8, scope: !22)
!69 = !DILocation(line: 230, column: 8, scope: !22)
!70 = !DILocation(line: 231, column: 1, scope: !22)
!71 = !DILocalVariable(name: "ctx", arg: 1, scope: !25, file: !1, line: 234, type: !11)
!72 = !DILocation(line: 234, column: 42, scope: !25)
!73 = !DILocalVariable(name: "out", arg: 2, scope: !25, file: !1, line: 234, type: !28)
!74 = !DILocation(line: 234, column: 56, scope: !25)
!75 = !DILocalVariable(name: "out_len", arg: 3, scope: !25, file: !1, line: 234, type: !29)
!76 = !DILocation(line: 234, column: 69, scope: !25)
!77 = !DILocation(line: 236, column: 8, scope: !25)
!78 = !DILocation(line: 237, column: 8, scope: !25)
!79 = !DILocation(line: 238, column: 8, scope: !25)
!80 = !DILocation(line: 239, column: 1, scope: !25)
!81 = !DILocalVariable(name: "ctx", arg: 1, scope: !30, file: !1, line: 242, type: !11)
!82 = !DILocation(line: 242, column: 44, scope: !30)
!83 = !DILocation(line: 244, column: 8, scope: !30)
!84 = !DILocation(line: 245, column: 1, scope: !30)
