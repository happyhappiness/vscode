; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cryptor.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive_cryptor = type { i32 (i8*, i64, i8*, i64, i32, i8*, i64)*, i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64, i8*, i64*)*, i32 (i32*)*, i32 (i32*, i8*, i64)*, i32 (i32*, i8*, i64, i8*, i64*)*, i32 (i32*)* }

@__archive_cryptor = constant %struct.archive_cryptor { i32 (i8*, i64, i8*, i64, i32, i8*, i64)* @pbkdf2_sha1, i32 (i32*, i8*, i64)* @aes_ctr_init, i32 (i32*, i8*, i64, i8*, i64*)* @aes_ctr_update, i32 (i32*)* @aes_ctr_release, i32 (i32*, i8*, i64)* @aes_ctr_init, i32 (i32*, i8*, i64, i8*, i64*)* @aes_ctr_update, i32 (i32*)* @aes_ctr_release }, align 8

; Function Attrs: nounwind uwtable
define i32 @__libarchive_cryptor_build_hack() #0 !dbg !4 {
entry:
  ret i32 0, !dbg !61
}

; Function Attrs: nounwind uwtable
define internal i32 @pbkdf2_sha1(i8* %pw, i64 %pw_len, i8* %salt, i64 %salt_len, i32 %rounds, i8* %derived_key, i64 %derived_key_len) #0 !dbg !8 {
entry:
  %pw.addr = alloca i8*, align 8
  %pw_len.addr = alloca i64, align 8
  %salt.addr = alloca i8*, align 8
  %salt_len.addr = alloca i64, align 8
  %rounds.addr = alloca i32, align 4
  %derived_key.addr = alloca i8*, align 8
  %derived_key_len.addr = alloca i64, align 8
  store i8* %pw, i8** %pw.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %pw.addr, metadata !62, metadata !63), !dbg !64
  store i64 %pw_len, i64* %pw_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %pw_len.addr, metadata !65, metadata !63), !dbg !66
  store i8* %salt, i8** %salt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %salt.addr, metadata !67, metadata !63), !dbg !68
  store i64 %salt_len, i64* %salt_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %salt_len.addr, metadata !69, metadata !63), !dbg !70
  store i32 %rounds, i32* %rounds.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %rounds.addr, metadata !71, metadata !63), !dbg !72
  store i8* %derived_key, i8** %derived_key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %derived_key.addr, metadata !73, metadata !63), !dbg !74
  store i64 %derived_key_len, i64* %derived_key_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %derived_key_len.addr, metadata !75, metadata !63), !dbg !76
  %0 = load i8*, i8** %pw.addr, align 8, !dbg !77
  %1 = load i64, i64* %pw_len.addr, align 8, !dbg !78
  %2 = load i8*, i8** %salt.addr, align 8, !dbg !79
  %3 = load i64, i64* %salt_len.addr, align 8, !dbg !80
  %4 = load i32, i32* %rounds.addr, align 4, !dbg !81
  %5 = load i8*, i8** %derived_key.addr, align 8, !dbg !82
  %6 = load i64, i64* %derived_key_len.addr, align 8, !dbg !83
  ret i32 -1, !dbg !84
}

; Function Attrs: nounwind uwtable
define internal i32 @aes_ctr_init(i32* %ctx, i8* %key, i64 %key_len) #0 !dbg !24 {
entry:
  %ctx.addr = alloca i32*, align 8
  %key.addr = alloca i8*, align 8
  %key_len.addr = alloca i64, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !85, metadata !63), !dbg !86
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !87, metadata !63), !dbg !88
  store i64 %key_len, i64* %key_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %key_len.addr, metadata !89, metadata !63), !dbg !90
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !91
  %1 = load i8*, i8** %key.addr, align 8, !dbg !92
  %2 = load i64, i64* %key_len.addr, align 8, !dbg !93
  ret i32 -1, !dbg !94
}

; Function Attrs: nounwind uwtable
define internal i32 @aes_ctr_update(i32* %ctx, i8* %in, i64 %in_len, i8* %out, i64* %out_len) #0 !dbg !30 {
entry:
  %ctx.addr = alloca i32*, align 8
  %in.addr = alloca i8*, align 8
  %in_len.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_len.addr = alloca i64*, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !95, metadata !63), !dbg !96
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !97, metadata !63), !dbg !98
  store i64 %in_len, i64* %in_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_len.addr, metadata !99, metadata !63), !dbg !100
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !101, metadata !63), !dbg !102
  store i64* %out_len, i64** %out_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_len.addr, metadata !103, metadata !63), !dbg !104
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !105
  %1 = load i8*, i8** %in.addr, align 8, !dbg !106
  %2 = load i64, i64* %in_len.addr, align 8, !dbg !107
  %3 = load i8*, i8** %out.addr, align 8, !dbg !108
  %4 = load i64*, i64** %out_len.addr, align 8, !dbg !109
  %5 = load i32*, i32** %ctx.addr, align 8, !dbg !110
  %call = call i32 @aes_ctr_encrypt_counter(i32* %5), !dbg !111
  ret i32 -1, !dbg !112
}

; Function Attrs: nounwind uwtable
define internal i32 @aes_ctr_release(i32* %ctx) #0 !dbg !39 {
entry:
  %ctx.addr = alloca i32*, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !113, metadata !63), !dbg !114
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !115
  ret i32 0, !dbg !116
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @aes_ctr_encrypt_counter(i32* %ctx) #0 !dbg !36 {
entry:
  %ctx.addr = alloca i32*, align 8
  store i32* %ctx, i32** %ctx.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ctx.addr, metadata !117, metadata !63), !dbg !118
  %0 = load i32*, i32** %ctx.addr, align 8, !dbg !119
  ret i32 -1, !dbg !120
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!58, !59}
!llvm.ident = !{!60}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !40)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cryptor.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !8, !24, !30, !36, !39}
!4 = distinct !DISubprogram(name: "__libarchive_cryptor_build_hack", scope: !1, file: !1, line: 43, type: !5, isLocal: false, isDefinition: true, scopeLine: 43, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{!7}
!7 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!8 = distinct !DISubprogram(name: "pbkdf2_sha1", scope: !1, file: !1, line: 115, type: !9, isLocal: true, isDefinition: true, scopeLine: 117, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!9 = !DISubroutineType(types: !10)
!10 = !{!7, !11, !14, !17, !14, !22, !23, !14}
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !13)
!13 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !15, line: 62, baseType: !16)
!15 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!16 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !19)
!19 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !20, line: 48, baseType: !21)
!20 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!21 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!22 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!24 = distinct !DISubprogram(name: "aes_ctr_init", scope: !1, file: !1, line: 353, type: !25, isLocal: true, isDefinition: true, scopeLine: 354, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!25 = !DISubroutineType(types: !26)
!26 = !{!7, !27, !17, !14}
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_crypto_ctx", file: !29, line: 120, baseType: !7)
!29 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_cryptor_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!30 = distinct !DISubprogram(name: "aes_ctr_update", scope: !1, file: !1, line: 379, type: !31, isLocal: true, isDefinition: true, scopeLine: 381, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!31 = !DISubroutineType(types: !32)
!32 = !{!7, !27, !33, !14, !34, !35}
!33 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !17)
!34 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !23)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64, align: 64)
!36 = distinct !DISubprogram(name: "aes_ctr_encrypt_counter", scope: !1, file: !1, line: 362, type: !37, isLocal: true, isDefinition: true, scopeLine: 363, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!37 = !DISubroutineType(types: !38)
!38 = !{!7, !27}
!39 = distinct !DISubprogram(name: "aes_ctr_release", scope: !1, file: !1, line: 369, type: !37, isLocal: true, isDefinition: true, scopeLine: 370, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!40 = !{!41}
!41 = !DIGlobalVariable(name: "__archive_cryptor", scope: !0, file: !1, line: 441, type: !42, isLocal: false, isDefinition: true, variable: %struct.archive_cryptor* @__archive_cryptor)
!42 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !43)
!43 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_cryptor", file: !29, line: 144, size: 448, align: 64, elements: !44)
!44 = !{!45, !47, !49, !53, !55, !56, !57}
!45 = !DIDerivedType(tag: DW_TAG_member, name: "pbkdf2sha1", scope: !43, file: !29, line: 147, baseType: !46, size: 64, align: 64)
!46 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "decrypto_aes_ctr_init", scope: !43, file: !29, line: 151, baseType: !48, size: 64, align: 64, offset: 64)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "decrypto_aes_ctr_update", scope: !43, file: !29, line: 152, baseType: !50, size: 64, align: 64, offset: 128)
!50 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!51 = !DISubroutineType(types: !52)
!52 = !{!7, !27, !17, !14, !23, !35}
!53 = !DIDerivedType(tag: DW_TAG_member, name: "decrypto_aes_ctr_release", scope: !43, file: !29, line: 154, baseType: !54, size: 64, align: 64, offset: 192)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "encrypto_aes_ctr_init", scope: !43, file: !29, line: 155, baseType: !48, size: 64, align: 64, offset: 256)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "encrypto_aes_ctr_update", scope: !43, file: !29, line: 156, baseType: !50, size: 64, align: 64, offset: 320)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "encrypto_aes_ctr_release", scope: !43, file: !29, line: 158, baseType: !54, size: 64, align: 64, offset: 384)
!58 = !{i32 2, !"Dwarf Version", i32 4}
!59 = !{i32 2, !"Debug Info Version", i32 3}
!60 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!61 = !DILocation(line: 44, column: 2, scope: !4)
!62 = !DILocalVariable(name: "pw", arg: 1, scope: !8, file: !1, line: 115, type: !11)
!63 = !DIExpression()
!64 = !DILocation(line: 115, column: 25, scope: !8)
!65 = !DILocalVariable(name: "pw_len", arg: 2, scope: !8, file: !1, line: 115, type: !14)
!66 = !DILocation(line: 115, column: 36, scope: !8)
!67 = !DILocalVariable(name: "salt", arg: 3, scope: !8, file: !1, line: 115, type: !17)
!68 = !DILocation(line: 115, column: 59, scope: !8)
!69 = !DILocalVariable(name: "salt_len", arg: 4, scope: !8, file: !1, line: 116, type: !14)
!70 = !DILocation(line: 116, column: 12, scope: !8)
!71 = !DILocalVariable(name: "rounds", arg: 5, scope: !8, file: !1, line: 116, type: !22)
!72 = !DILocation(line: 116, column: 31, scope: !8)
!73 = !DILocalVariable(name: "derived_key", arg: 6, scope: !8, file: !1, line: 116, type: !23)
!74 = !DILocation(line: 116, column: 48, scope: !8)
!75 = !DILocalVariable(name: "derived_key_len", arg: 7, scope: !8, file: !1, line: 117, type: !14)
!76 = !DILocation(line: 117, column: 12, scope: !8)
!77 = !DILocation(line: 118, column: 8, scope: !8)
!78 = !DILocation(line: 119, column: 8, scope: !8)
!79 = !DILocation(line: 120, column: 8, scope: !8)
!80 = !DILocation(line: 121, column: 8, scope: !8)
!81 = !DILocation(line: 122, column: 8, scope: !8)
!82 = !DILocation(line: 123, column: 8, scope: !8)
!83 = !DILocation(line: 124, column: 8, scope: !8)
!84 = !DILocation(line: 125, column: 2, scope: !8)
!85 = !DILocalVariable(name: "ctx", arg: 1, scope: !24, file: !1, line: 353, type: !27)
!86 = !DILocation(line: 353, column: 34, scope: !24)
!87 = !DILocalVariable(name: "key", arg: 2, scope: !24, file: !1, line: 353, type: !17)
!88 = !DILocation(line: 353, column: 54, scope: !24)
!89 = !DILocalVariable(name: "key_len", arg: 3, scope: !24, file: !1, line: 353, type: !14)
!90 = !DILocation(line: 353, column: 66, scope: !24)
!91 = !DILocation(line: 355, column: 8, scope: !24)
!92 = !DILocation(line: 356, column: 8, scope: !24)
!93 = !DILocation(line: 357, column: 8, scope: !24)
!94 = !DILocation(line: 358, column: 2, scope: !24)
!95 = !DILocalVariable(name: "ctx", arg: 1, scope: !30, file: !1, line: 379, type: !27)
!96 = !DILocation(line: 379, column: 36, scope: !30)
!97 = !DILocalVariable(name: "in", arg: 2, scope: !30, file: !1, line: 379, type: !33)
!98 = !DILocation(line: 379, column: 63, scope: !30)
!99 = !DILocalVariable(name: "in_len", arg: 3, scope: !30, file: !1, line: 380, type: !14)
!100 = !DILocation(line: 380, column: 12, scope: !30)
!101 = !DILocalVariable(name: "out", arg: 4, scope: !30, file: !1, line: 380, type: !34)
!102 = !DILocation(line: 380, column: 36, scope: !30)
!103 = !DILocalVariable(name: "out_len", arg: 5, scope: !30, file: !1, line: 380, type: !35)
!104 = !DILocation(line: 380, column: 49, scope: !30)
!105 = !DILocation(line: 382, column: 8, scope: !30)
!106 = !DILocation(line: 383, column: 8, scope: !30)
!107 = !DILocation(line: 384, column: 8, scope: !30)
!108 = !DILocation(line: 385, column: 8, scope: !30)
!109 = !DILocation(line: 386, column: 8, scope: !30)
!110 = !DILocation(line: 387, column: 26, scope: !30)
!111 = !DILocation(line: 387, column: 2, scope: !30)
!112 = !DILocation(line: 388, column: 2, scope: !30)
!113 = !DILocalVariable(name: "ctx", arg: 1, scope: !39, file: !1, line: 369, type: !27)
!114 = !DILocation(line: 369, column: 37, scope: !39)
!115 = !DILocation(line: 371, column: 8, scope: !39)
!116 = !DILocation(line: 372, column: 2, scope: !39)
!117 = !DILocalVariable(name: "ctx", arg: 1, scope: !36, file: !1, line: 362, type: !27)
!118 = !DILocation(line: 362, column: 45, scope: !36)
!119 = !DILocation(line: 364, column: 8, scope: !36)
!120 = !DILocation(line: 365, column: 2, scope: !36)
