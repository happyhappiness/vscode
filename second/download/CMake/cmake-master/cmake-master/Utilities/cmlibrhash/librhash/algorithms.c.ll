; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/algorithms.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.rhash_hash_info = type { %struct.rhash_info*, i64, i64, void (i8*)*, void (i8*, i8*, i64)*, void (i8*, i8*)*, void (i8*)* }
%struct.rhash_info = type { i32, i32, i64, i8*, i8* }
%struct.md5_ctx = type { [16 x i32], i64, [4 x i32] }
%struct.sha1_ctx = type { [64 x i8], i64, [5 x i32] }
%struct.sha256_ctx = type { [16 x i32], i64, [8 x i32], i32 }
%struct.sha512_ctx = type { [16 x i64], i64, [8 x i64], i32 }
%struct.sha3_ctx = type { [25 x i64], [24 x i64], i32, i32 }

@rhash_uninitialized_algorithms = global i32 0, align 4
@rhash_hash_info_default = global [10 x %struct.rhash_hash_info] [%struct.rhash_hash_info { %struct.rhash_info* @info_md5, i64 88, i64 72, void (i8*)* bitcast (void (%struct.md5_ctx*)* @rhash_md5_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.md5_ctx*, i8*, i64)* @rhash_md5_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.md5_ctx*, i8*)* @rhash_md5_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha1, i64 96, i64 72, void (i8*)* bitcast (void (%struct.sha1_ctx*)* @rhash_sha1_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha1_ctx*, i8*, i64)* @rhash_sha1_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha1_ctx*, i8*)* @rhash_sha1_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha224, i64 112, i64 72, void (i8*)* bitcast (void (%struct.sha256_ctx*)* @rhash_sha224_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha256_ctx*, i8*, i64)* @rhash_sha256_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha256_ctx*, i8*)* @rhash_sha256_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha256, i64 112, i64 72, void (i8*)* bitcast (void (%struct.sha256_ctx*)* @rhash_sha256_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha256_ctx*, i8*, i64)* @rhash_sha256_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha256_ctx*, i8*)* @rhash_sha256_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha384, i64 208, i64 136, void (i8*)* bitcast (void (%struct.sha512_ctx*)* @rhash_sha384_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha512_ctx*, i8*, i64)* @rhash_sha512_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha512_ctx*, i8*)* @rhash_sha512_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha512, i64 208, i64 136, void (i8*)* bitcast (void (%struct.sha512_ctx*)* @rhash_sha512_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha512_ctx*, i8*, i64)* @rhash_sha512_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha512_ctx*, i8*)* @rhash_sha512_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha3_224, i64 400, i64 0, void (i8*)* bitcast (void (%struct.sha3_ctx*)* @rhash_sha3_224_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha3_ctx*, i8*, i64)* @rhash_sha3_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha3_ctx*, i8*)* @rhash_sha3_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha3_256, i64 400, i64 0, void (i8*)* bitcast (void (%struct.sha3_ctx*)* @rhash_sha3_256_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha3_ctx*, i8*, i64)* @rhash_sha3_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha3_ctx*, i8*)* @rhash_sha3_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha3_384, i64 400, i64 0, void (i8*)* bitcast (void (%struct.sha3_ctx*)* @rhash_sha3_384_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha3_ctx*, i8*, i64)* @rhash_sha3_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha3_ctx*, i8*)* @rhash_sha3_final to void (i8*, i8*)*), void (i8*)* null }, %struct.rhash_hash_info { %struct.rhash_info* @info_sha3_512, i64 400, i64 0, void (i8*)* bitcast (void (%struct.sha3_ctx*)* @rhash_sha3_512_init to void (i8*)*), void (i8*, i8*, i64)* bitcast (void (%struct.sha3_ctx*, i8*, i64)* @rhash_sha3_update to void (i8*, i8*, i64)*), void (i8*, i8*)* bitcast (void (%struct.sha3_ctx*, i8*)* @rhash_sha3_final to void (i8*, i8*)*), void (i8*)* null }], align 16
@rhash_info_table = global %struct.rhash_hash_info* getelementptr inbounds ([10 x %struct.rhash_hash_info], [10 x %struct.rhash_hash_info]* @rhash_hash_info_default, i32 0, i32 0), align 8
@rhash_info_size = global i32 10, align 4
@.str = private unnamed_addr constant [4 x i8] c"MD5\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"md5\00", align 1
@info_md5 = global %struct.rhash_info { i32 1, i32 0, i64 16, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0) }, align 8
@.str.2 = private unnamed_addr constant [5 x i8] c"SHA1\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c"sha1\00", align 1
@info_sha1 = global %struct.rhash_info { i32 2, i32 2, i64 20, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0) }, align 8
@.str.4 = private unnamed_addr constant [8 x i8] c"SHA-224\00", align 1
@.str.5 = private unnamed_addr constant [7 x i8] c"sha224\00", align 1
@info_sha224 = global %struct.rhash_info { i32 4, i32 2, i64 28, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.5, i32 0, i32 0) }, align 8
@.str.6 = private unnamed_addr constant [8 x i8] c"SHA-256\00", align 1
@.str.7 = private unnamed_addr constant [7 x i8] c"sha256\00", align 1
@info_sha256 = global %struct.rhash_info { i32 8, i32 2, i64 32, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0) }, align 8
@.str.8 = private unnamed_addr constant [8 x i8] c"SHA-384\00", align 1
@.str.9 = private unnamed_addr constant [7 x i8] c"sha384\00", align 1
@info_sha384 = global %struct.rhash_info { i32 16, i32 4, i64 48, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.9, i32 0, i32 0) }, align 8
@.str.10 = private unnamed_addr constant [8 x i8] c"SHA-512\00", align 1
@.str.11 = private unnamed_addr constant [7 x i8] c"sha512\00", align 1
@info_sha512 = global %struct.rhash_info { i32 32, i32 4, i64 64, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.11, i32 0, i32 0) }, align 8
@.str.12 = private unnamed_addr constant [9 x i8] c"SHA3-224\00", align 1
@.str.13 = private unnamed_addr constant [9 x i8] c"sha3-224\00", align 1
@info_sha3_224 = global %struct.rhash_info { i32 64, i32 0, i64 28, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.13, i32 0, i32 0) }, align 8
@.str.14 = private unnamed_addr constant [9 x i8] c"SHA3-256\00", align 1
@.str.15 = private unnamed_addr constant [9 x i8] c"sha3-256\00", align 1
@info_sha3_256 = global %struct.rhash_info { i32 128, i32 0, i64 32, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.15, i32 0, i32 0) }, align 8
@.str.16 = private unnamed_addr constant [9 x i8] c"SHA3-384\00", align 1
@.str.17 = private unnamed_addr constant [9 x i8] c"sha3-384\00", align 1
@info_sha3_384 = global %struct.rhash_info { i32 256, i32 0, i64 48, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.17, i32 0, i32 0) }, align 8
@.str.18 = private unnamed_addr constant [9 x i8] c"SHA3-512\00", align 1
@.str.19 = private unnamed_addr constant [9 x i8] c"sha3-512\00", align 1
@info_sha3_512 = global %struct.rhash_info { i32 512, i32 0, i64 64, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.18, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.19, i32 0, i32 0) }, align 8

declare void @rhash_md5_init(%struct.md5_ctx*) #0

declare void @rhash_md5_update(%struct.md5_ctx*, i8*, i64) #0

declare void @rhash_md5_final(%struct.md5_ctx*, i8*) #0

declare void @rhash_sha1_init(%struct.sha1_ctx*) #0

declare void @rhash_sha1_update(%struct.sha1_ctx*, i8*, i64) #0

declare void @rhash_sha1_final(%struct.sha1_ctx*, i8*) #0

declare void @rhash_sha224_init(%struct.sha256_ctx*) #0

declare void @rhash_sha256_update(%struct.sha256_ctx*, i8*, i64) #0

declare void @rhash_sha256_final(%struct.sha256_ctx*, i8*) #0

declare void @rhash_sha256_init(%struct.sha256_ctx*) #0

declare void @rhash_sha384_init(%struct.sha512_ctx*) #0

declare void @rhash_sha512_update(%struct.sha512_ctx*, i8*, i64) #0

declare void @rhash_sha512_final(%struct.sha512_ctx*, i8*) #0

declare void @rhash_sha512_init(%struct.sha512_ctx*) #0

declare void @rhash_sha3_224_init(%struct.sha3_ctx*) #0

declare void @rhash_sha3_update(%struct.sha3_ctx*, i8*, i64) #0

declare void @rhash_sha3_final(%struct.sha3_ctx*, i8*) #0

declare void @rhash_sha3_256_init(%struct.sha3_ctx*) #0

declare void @rhash_sha3_384_init(%struct.sha3_ctx*) #0

declare void @rhash_sha3_512_init(%struct.sha3_ctx*) #0

; Function Attrs: nounwind uwtable
define void @rhash_init_algorithms(i32 %mask) #1 !dbg !4 {
entry:
  %mask.addr = alloca i32, align 4
  store i32 %mask, i32* %mask.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mask.addr, metadata !78, metadata !79), !dbg !80
  %0 = load i32, i32* %mask.addr, align 4, !dbg !81
  store i32 0, i32* @rhash_uninitialized_algorithms, align 4, !dbg !82
  ret void, !dbg !83
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

attributes #0 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readnone }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!75, !76}
!llvm.ident = !{!77}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, subprograms: !3, globals: !8)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/algorithms.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!2 = !{}
!3 = !{!4}
!4 = distinct !DISubprogram(name: "rhash_init_algorithms", scope: !1, file: !1, line: 161, type: !5, isLocal: false, isDefinition: true, scopeLine: 162, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!5 = !DISubroutineType(types: !6)
!6 = !{null, !7}
!7 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!8 = !{!9, !10, !59, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71}
!9 = !DIGlobalVariable(name: "rhash_uninitialized_algorithms", scope: !0, file: !1, line: 69, type: !7, isLocal: false, isDefinition: true, variable: i32* @rhash_uninitialized_algorithms)
!10 = !DIGlobalVariable(name: "rhash_info_table", scope: !0, file: !1, line: 71, type: !11, isLocal: false, isDefinition: true, variable: %struct.rhash_hash_info** @rhash_info_table)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "rhash_hash_info", file: !13, line: 35, baseType: !14)
!13 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/algorithms.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!14 = !DICompositeType(tag: DW_TAG_structure_type, name: "rhash_hash_info", file: !13, line: 26, size: 448, align: 64, elements: !15)
!15 = !{!16, !33, !34, !37, !43, !50, !57}
!16 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !14, file: !13, line: 28, baseType: !17, size: 64, align: 64)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DIDerivedType(tag: DW_TAG_typedef, name: "rhash_info", file: !19, line: 151, baseType: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibrhash/librhash/rhash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!20 = !DICompositeType(tag: DW_TAG_structure_type, name: "rhash_info", file: !19, line: 141, size: 256, align: 64, elements: !21)
!21 = !{!22, !23, !24, !28, !32}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "hash_id", scope: !20, file: !19, line: 144, baseType: !7, size: 32, align: 32)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !20, file: !19, line: 146, baseType: !7, size: 32, align: 32, offset: 32)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "digest_size", scope: !20, file: !19, line: 148, baseType: !25, size: 64, align: 64, offset: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !26, line: 62, baseType: !27)
!26 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibrhash")
!27 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!28 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !20, file: !19, line: 149, baseType: !29, size: 64, align: 64, offset: 128)
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !31)
!31 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "magnet_name", scope: !20, file: !19, line: 150, baseType: !29, size: 64, align: 64, offset: 192)
!33 = !DIDerivedType(tag: DW_TAG_member, name: "context_size", scope: !14, file: !13, line: 29, baseType: !25, size: 64, align: 64, offset: 64)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "digest_diff", scope: !14, file: !13, line: 30, baseType: !35, size: 64, align: 64, offset: 128)
!35 = !DIDerivedType(tag: DW_TAG_typedef, name: "ptrdiff_t", file: !26, line: 51, baseType: !36)
!36 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !14, file: !13, line: 31, baseType: !38, size: 64, align: 64, offset: 192)
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "pinit_t", file: !13, line: 18, baseType: !39)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DISubroutineType(types: !41)
!41 = !{null, !42}
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!43 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !14, file: !13, line: 32, baseType: !44, size: 64, align: 64, offset: 256)
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "pupdate_t", file: !13, line: 19, baseType: !45)
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!46 = !DISubroutineType(types: !47)
!47 = !{null, !42, !48, !25}
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "final", scope: !14, file: !13, line: 33, baseType: !51, size: 64, align: 64, offset: 320)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "pfinal_t", file: !13, line: 20, baseType: !52)
!52 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !53, size: 64, align: 64)
!53 = !DISubroutineType(types: !54)
!54 = !{null, !42, !55}
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !14, file: !13, line: 34, baseType: !58, size: 64, align: 64, offset: 384)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "pcleanup_t", file: !13, line: 21, baseType: !39)
!59 = !DIGlobalVariable(name: "rhash_info_size", scope: !0, file: !1, line: 72, type: !60, isLocal: false, isDefinition: true, variable: i32* @rhash_info_size)
!60 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!61 = !DIGlobalVariable(name: "info_md5", scope: !0, file: !1, line: 84, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_md5)
!62 = !DIGlobalVariable(name: "info_sha1", scope: !0, file: !1, line: 85, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha1)
!63 = !DIGlobalVariable(name: "info_sha224", scope: !0, file: !1, line: 100, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha224)
!64 = !DIGlobalVariable(name: "info_sha256", scope: !0, file: !1, line: 101, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha256)
!65 = !DIGlobalVariable(name: "info_sha384", scope: !0, file: !1, line: 102, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha384)
!66 = !DIGlobalVariable(name: "info_sha512", scope: !0, file: !1, line: 103, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha512)
!67 = !DIGlobalVariable(name: "info_sha3_224", scope: !0, file: !1, line: 108, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha3_224)
!68 = !DIGlobalVariable(name: "info_sha3_256", scope: !0, file: !1, line: 109, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha3_256)
!69 = !DIGlobalVariable(name: "info_sha3_384", scope: !0, file: !1, line: 110, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha3_384)
!70 = !DIGlobalVariable(name: "info_sha3_512", scope: !0, file: !1, line: 111, type: !18, isLocal: false, isDefinition: true, variable: %struct.rhash_info* @info_sha3_512)
!71 = !DIGlobalVariable(name: "rhash_hash_info_default", scope: !0, file: !1, line: 123, type: !72, isLocal: false, isDefinition: true, variable: [10 x %struct.rhash_hash_info]* @rhash_hash_info_default)
!72 = !DICompositeType(tag: DW_TAG_array_type, baseType: !12, size: 4480, align: 64, elements: !73)
!73 = !{!74}
!74 = !DISubrange(count: 10)
!75 = !{i32 2, !"Dwarf Version", i32 4}
!76 = !{i32 2, !"Debug Info Version", i32 3}
!77 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!78 = !DILocalVariable(name: "mask", arg: 1, scope: !4, file: !1, line: 161, type: !7)
!79 = !DIExpression()
!80 = !DILocation(line: 161, column: 37, scope: !4)
!81 = !DILocation(line: 163, column: 8, scope: !4)
!82 = !DILocation(line: 174, column: 33, scope: !4)
!83 = !DILocation(line: 175, column: 1, scope: !4)
