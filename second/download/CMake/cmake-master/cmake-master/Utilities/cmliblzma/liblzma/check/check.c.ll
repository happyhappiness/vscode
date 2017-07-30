; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_check_state = type { %union.anon, %union.anon.0 }
%union.anon = type { [8 x i64] }
%union.anon.0 = type { %struct.anon }
%struct.anon = type { [8 x i32], i64 }

@lzma_check_is_supported.available_checks = internal constant [16 x i8] c"\01\01\00\00\01\00\00\00\00\00\01\00\00\00\00\00", align 16
@lzma_check_size.check_sizes = internal constant [16 x i8] c"\00\04\04\04\08\08\08\10\10\10   @@@", align 16

; Function Attrs: nounwind readnone uwtable
define zeroext i8 @lzma_check_is_supported(i32 %type) #0 !dbg !17 {
entry:
  %retval = alloca i8, align 1
  %type.addr = alloca i32, align 4
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !80, metadata !81), !dbg !82
  %0 = load i32, i32* %type.addr, align 4, !dbg !83
  %cmp = icmp ugt i32 %0, 15, !dbg !85
  br i1 %cmp, label %if.then, label %if.end, !dbg !86

if.then:                                          ; preds = %entry
  store i8 0, i8* %retval, align 1, !dbg !87
  br label %return, !dbg !87

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %type.addr, align 4, !dbg !88
  %idxprom = zext i32 %1 to i64, !dbg !89
  %arrayidx = getelementptr inbounds [16 x i8], [16 x i8]* @lzma_check_is_supported.available_checks, i64 0, i64 %idxprom, !dbg !89
  %2 = load i8, i8* %arrayidx, align 1, !dbg !89
  store i8 %2, i8* %retval, align 1, !dbg !90
  br label %return, !dbg !90

return:                                           ; preds = %if.end, %if.then
  %3 = load i8, i8* %retval, align 1, !dbg !91
  ret i8 %3, !dbg !91
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind readnone uwtable
define i32 @lzma_check_size(i32 %type) #0 !dbg !25 {
entry:
  %retval = alloca i32, align 4
  %type.addr = alloca i32, align 4
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !92, metadata !81), !dbg !93
  %0 = load i32, i32* %type.addr, align 4, !dbg !94
  %cmp = icmp ugt i32 %0, 15, !dbg !96
  br i1 %cmp, label %if.then, label %if.end, !dbg !97

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !98
  br label %return, !dbg !98

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %type.addr, align 4, !dbg !99
  %idxprom = zext i32 %1 to i64, !dbg !100
  %arrayidx = getelementptr inbounds [16 x i8], [16 x i8]* @lzma_check_size.check_sizes, i64 0, i64 %idxprom, !dbg !100
  %2 = load i8, i8* %arrayidx, align 1, !dbg !100
  %conv = zext i8 %2 to i32, !dbg !100
  store i32 %conv, i32* %retval, align 4, !dbg !101
  br label %return, !dbg !101

return:                                           ; preds = %if.end, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !102
  ret i32 %3, !dbg !102
}

; Function Attrs: nounwind uwtable
define void @lzma_check_init(%struct.lzma_check_state* %check, i32 %type) #2 !dbg !28 {
entry:
  %check.addr = alloca %struct.lzma_check_state*, align 8
  %type.addr = alloca i32, align 4
  store %struct.lzma_check_state* %check, %struct.lzma_check_state** %check.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state** %check.addr, metadata !103, metadata !81), !dbg !104
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !105, metadata !81), !dbg !106
  %0 = load i32, i32* %type.addr, align 4, !dbg !107
  switch i32 %0, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb1
    i32 4, label %sw.bb2
    i32 10, label %sw.bb4
  ], !dbg !108

sw.bb:                                            ; preds = %entry
  br label %sw.epilog, !dbg !109

sw.bb1:                                           ; preds = %entry
  %1 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !111
  %state = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %1, i32 0, i32 1, !dbg !112
  %crc32 = bitcast %union.anon.0* %state to i32*, !dbg !113
  store i32 0, i32* %crc32, align 8, !dbg !114
  br label %sw.epilog, !dbg !115

sw.bb2:                                           ; preds = %entry
  %2 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !116
  %state3 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %2, i32 0, i32 1, !dbg !117
  %crc64 = bitcast %union.anon.0* %state3 to i64*, !dbg !118
  store i64 0, i64* %crc64, align 8, !dbg !119
  br label %sw.epilog, !dbg !120

sw.bb4:                                           ; preds = %entry
  %3 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !121
  call void @lzma_sha256_init(%struct.lzma_check_state* %3), !dbg !122
  br label %sw.epilog, !dbg !123

sw.default:                                       ; preds = %entry
  br label %sw.epilog, !dbg !124

sw.epilog:                                        ; preds = %sw.default, %sw.bb4, %sw.bb2, %sw.bb1, %sw.bb
  ret void, !dbg !125
}

declare void @lzma_sha256_init(%struct.lzma_check_state*) #3

; Function Attrs: nounwind uwtable
define void @lzma_check_update(%struct.lzma_check_state* %check, i32 %type, i8* %buf, i64 %size) #2 !dbg !63 {
entry:
  %check.addr = alloca %struct.lzma_check_state*, align 8
  %type.addr = alloca i32, align 4
  %buf.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store %struct.lzma_check_state* %check, %struct.lzma_check_state** %check.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state** %check.addr, metadata !126, metadata !81), !dbg !127
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !128, metadata !81), !dbg !129
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !130, metadata !81), !dbg !131
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !132, metadata !81), !dbg !133
  %0 = load i32, i32* %type.addr, align 4, !dbg !134
  switch i32 %0, label %sw.default [
    i32 1, label %sw.bb
    i32 4, label %sw.bb3
    i32 10, label %sw.bb8
  ], !dbg !135

sw.bb:                                            ; preds = %entry
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !136
  %2 = load i64, i64* %size.addr, align 8, !dbg !138
  %3 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !139
  %state = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %3, i32 0, i32 1, !dbg !140
  %crc32 = bitcast %union.anon.0* %state to i32*, !dbg !141
  %4 = load i32, i32* %crc32, align 8, !dbg !141
  %call = call i32 @lzma_crc32(i8* %1, i64 %2, i32 %4) #5, !dbg !142
  %5 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !143
  %state1 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %5, i32 0, i32 1, !dbg !144
  %crc322 = bitcast %union.anon.0* %state1 to i32*, !dbg !145
  store i32 %call, i32* %crc322, align 8, !dbg !146
  br label %sw.epilog, !dbg !147

sw.bb3:                                           ; preds = %entry
  %6 = load i8*, i8** %buf.addr, align 8, !dbg !148
  %7 = load i64, i64* %size.addr, align 8, !dbg !149
  %8 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !150
  %state4 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %8, i32 0, i32 1, !dbg !151
  %crc64 = bitcast %union.anon.0* %state4 to i64*, !dbg !152
  %9 = load i64, i64* %crc64, align 8, !dbg !152
  %call5 = call i64 @lzma_crc64(i8* %6, i64 %7, i64 %9) #5, !dbg !153
  %10 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !154
  %state6 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %10, i32 0, i32 1, !dbg !155
  %crc647 = bitcast %union.anon.0* %state6 to i64*, !dbg !156
  store i64 %call5, i64* %crc647, align 8, !dbg !157
  br label %sw.epilog, !dbg !158

sw.bb8:                                           ; preds = %entry
  %11 = load i8*, i8** %buf.addr, align 8, !dbg !159
  %12 = load i64, i64* %size.addr, align 8, !dbg !160
  %13 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !161
  call void @lzma_sha256_update(i8* %11, i64 %12, %struct.lzma_check_state* %13), !dbg !162
  br label %sw.epilog, !dbg !163

sw.default:                                       ; preds = %entry
  br label %sw.epilog, !dbg !164

sw.epilog:                                        ; preds = %sw.default, %sw.bb8, %sw.bb3, %sw.bb
  ret void, !dbg !165
}

; Function Attrs: nounwind readonly
declare i32 @lzma_crc32(i8*, i64, i32) #4

; Function Attrs: nounwind readonly
declare i64 @lzma_crc64(i8*, i64, i64) #4

declare void @lzma_sha256_update(i8*, i64, %struct.lzma_check_state*) #3

; Function Attrs: nounwind uwtable
define void @lzma_check_finish(%struct.lzma_check_state* %check, i32 %type) #2 !dbg !70 {
entry:
  %check.addr = alloca %struct.lzma_check_state*, align 8
  %type.addr = alloca i32, align 4
  store %struct.lzma_check_state* %check, %struct.lzma_check_state** %check.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_check_state** %check.addr, metadata !166, metadata !81), !dbg !167
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !168, metadata !81), !dbg !169
  %0 = load i32, i32* %type.addr, align 4, !dbg !170
  switch i32 %0, label %sw.default [
    i32 1, label %sw.bb
    i32 4, label %sw.bb1
    i32 10, label %sw.bb5
  ], !dbg !171

sw.bb:                                            ; preds = %entry
  %1 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !172
  %state = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %1, i32 0, i32 1, !dbg !172
  %crc32 = bitcast %union.anon.0* %state to i32*, !dbg !172
  %2 = load i32, i32* %crc32, align 8, !dbg !172
  %3 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !174
  %buffer = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %3, i32 0, i32 0, !dbg !175
  %u32 = bitcast %union.anon* %buffer to [16 x i32]*, !dbg !176
  %arrayidx = getelementptr inbounds [16 x i32], [16 x i32]* %u32, i64 0, i64 0, !dbg !174
  store i32 %2, i32* %arrayidx, align 8, !dbg !177
  br label %sw.epilog, !dbg !178

sw.bb1:                                           ; preds = %entry
  %4 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !179
  %state2 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %4, i32 0, i32 1, !dbg !179
  %crc64 = bitcast %union.anon.0* %state2 to i64*, !dbg !179
  %5 = load i64, i64* %crc64, align 8, !dbg !179
  %6 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !180
  %buffer3 = getelementptr inbounds %struct.lzma_check_state, %struct.lzma_check_state* %6, i32 0, i32 0, !dbg !181
  %u64 = bitcast %union.anon* %buffer3 to [8 x i64]*, !dbg !182
  %arrayidx4 = getelementptr inbounds [8 x i64], [8 x i64]* %u64, i64 0, i64 0, !dbg !180
  store i64 %5, i64* %arrayidx4, align 8, !dbg !183
  br label %sw.epilog, !dbg !184

sw.bb5:                                           ; preds = %entry
  %7 = load %struct.lzma_check_state*, %struct.lzma_check_state** %check.addr, align 8, !dbg !185
  call void @lzma_sha256_finish(%struct.lzma_check_state* %7), !dbg !186
  br label %sw.epilog, !dbg !187

sw.default:                                       ; preds = %entry
  br label %sw.epilog, !dbg !188

sw.epilog:                                        ; preds = %sw.default, %sw.bb5, %sw.bb1, %sw.bb
  ret void, !dbg !189
}

declare void @lzma_sha256_finish(%struct.lzma_check_state*) #3

attributes #0 = { nounwind readnone uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!77, !78}
!llvm.ident = !{!79}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !10, subprograms: !16, globals: !71)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 27, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!5 = !{!6, !7, !8, !9}
!6 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!7 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!8 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!9 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!10 = !{!11, !12, !14}
!11 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !13, line: 51, baseType: !11)
!13 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!14 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !13, line: 55, baseType: !15)
!15 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!16 = !{!17, !25, !28, !63, !70}
!17 = distinct !DISubprogram(name: "lzma_check_is_supported", scope: !1, file: !1, line: 17, type: !18, isLocal: false, isDefinition: true, scopeLine: 18, flags: DIFlagPrototyped, isOptimized: false, variables: !24)
!18 = !DISubroutineType(types: !19)
!19 = !{!20, !23}
!20 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_bool", file: !21, line: 29, baseType: !22)
!21 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/base.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!22 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!23 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !4, line: 55, baseType: !3)
!24 = !{}
!25 = distinct !DISubprogram(name: "lzma_check_size", scope: !1, file: !1, line: 64, type: !26, isLocal: false, isDefinition: true, scopeLine: 65, flags: DIFlagPrototyped, isOptimized: false, variables: !24)
!26 = !DISubroutineType(types: !27)
!27 = !{!12, !23}
!28 = distinct !DISubprogram(name: "lzma_check_init", scope: !1, file: !1, line: 84, type: !29, isLocal: false, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: false, variables: !24)
!29 = !DISubroutineType(types: !30)
!30 = !{null, !31, !23}
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check_state", file: !33, line: 56, baseType: !34)
!33 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/check/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!34 = !DICompositeType(tag: DW_TAG_structure_type, file: !33, line: 34, size: 832, align: 64, elements: !35)
!35 = !{!36, !52}
!36 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !34, file: !33, line: 40, baseType: !37, size: 512, align: 64)
!37 = !DICompositeType(tag: DW_TAG_union_type, scope: !34, file: !33, line: 36, size: 512, align: 64, elements: !38)
!38 = !{!39, !44, !48}
!39 = !DIDerivedType(tag: DW_TAG_member, name: "u8", scope: !37, file: !33, line: 37, baseType: !40, size: 512, align: 8)
!40 = !DICompositeType(tag: DW_TAG_array_type, baseType: !41, size: 512, align: 8, elements: !42)
!41 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !13, line: 48, baseType: !22)
!42 = !{!43}
!43 = !DISubrange(count: 64)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "u32", scope: !37, file: !33, line: 38, baseType: !45, size: 512, align: 32)
!45 = !DICompositeType(tag: DW_TAG_array_type, baseType: !12, size: 512, align: 32, elements: !46)
!46 = !{!47}
!47 = !DISubrange(count: 16)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "u64", scope: !37, file: !33, line: 39, baseType: !49, size: 512, align: 64)
!49 = !DICompositeType(tag: DW_TAG_array_type, baseType: !14, size: 512, align: 64, elements: !50)
!50 = !{!51}
!51 = !DISubrange(count: 8)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !34, file: !33, line: 54, baseType: !53, size: 320, align: 64, offset: 512)
!53 = !DICompositeType(tag: DW_TAG_union_type, scope: !34, file: !33, line: 43, size: 320, align: 64, elements: !54)
!54 = !{!55, !56, !57}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "crc32", scope: !53, file: !33, line: 44, baseType: !12, size: 32, align: 32)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "crc64", scope: !53, file: !33, line: 45, baseType: !14, size: 64, align: 64)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "sha256", scope: !53, file: !33, line: 53, baseType: !58, size: 320, align: 64)
!58 = !DICompositeType(tag: DW_TAG_structure_type, scope: !53, file: !33, line: 47, size: 320, align: 64, elements: !59)
!59 = !{!60, !62}
!60 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !58, file: !33, line: 49, baseType: !61, size: 256, align: 32)
!61 = !DICompositeType(tag: DW_TAG_array_type, baseType: !12, size: 256, align: 32, elements: !50)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !58, file: !33, line: 52, baseType: !14, size: 64, align: 64, offset: 256)
!63 = distinct !DISubprogram(name: "lzma_check_update", scope: !1, file: !1, line: 117, type: !64, isLocal: false, isDefinition: true, scopeLine: 119, flags: DIFlagPrototyped, isOptimized: false, variables: !24)
!64 = !DISubroutineType(types: !65)
!65 = !{null, !31, !23, !66, !68}
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !41)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !69, line: 62, baseType: !15)
!69 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!70 = distinct !DISubprogram(name: "lzma_check_finish", scope: !1, file: !1, line: 148, type: !29, isLocal: false, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !24)
!71 = !{!72, !75}
!72 = !DIGlobalVariable(name: "available_checks", scope: !17, file: !1, line: 19, type: !73, isLocal: true, isDefinition: true, variable: [16 x i8]* @lzma_check_is_supported.available_checks)
!73 = !DICompositeType(tag: DW_TAG_array_type, baseType: !74, size: 128, align: 8, elements: !46)
!74 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !20)
!75 = !DIGlobalVariable(name: "check_sizes", scope: !25, file: !1, line: 67, type: !76, isLocal: true, isDefinition: true, variable: [16 x i8]* @lzma_check_size.check_sizes)
!76 = !DICompositeType(tag: DW_TAG_array_type, baseType: !67, size: 128, align: 8, elements: !46)
!77 = !{i32 2, !"Dwarf Version", i32 4}
!78 = !{i32 2, !"Debug Info Version", i32 3}
!79 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!80 = !DILocalVariable(name: "type", arg: 1, scope: !17, file: !1, line: 17, type: !23)
!81 = !DIExpression()
!82 = !DILocation(line: 17, column: 36, scope: !17)
!83 = !DILocation(line: 56, column: 21, scope: !84)
!84 = distinct !DILexicalBlock(scope: !17, file: !1, line: 56, column: 6)
!85 = !DILocation(line: 56, column: 27, scope: !84)
!86 = !DILocation(line: 56, column: 6, scope: !17)
!87 = !DILocation(line: 57, column: 3, scope: !84)
!88 = !DILocation(line: 59, column: 41, scope: !17)
!89 = !DILocation(line: 59, column: 9, scope: !17)
!90 = !DILocation(line: 59, column: 2, scope: !17)
!91 = !DILocation(line: 60, column: 1, scope: !17)
!92 = !DILocalVariable(name: "type", arg: 1, scope: !25, file: !1, line: 64, type: !23)
!93 = !DILocation(line: 64, column: 28, scope: !25)
!94 = !DILocation(line: 76, column: 21, scope: !95)
!95 = distinct !DILexicalBlock(scope: !25, file: !1, line: 76, column: 6)
!96 = !DILocation(line: 76, column: 27, scope: !95)
!97 = !DILocation(line: 76, column: 6, scope: !25)
!98 = !DILocation(line: 77, column: 3, scope: !95)
!99 = !DILocation(line: 79, column: 36, scope: !25)
!100 = !DILocation(line: 79, column: 9, scope: !25)
!101 = !DILocation(line: 79, column: 2, scope: !25)
!102 = !DILocation(line: 80, column: 1, scope: !25)
!103 = !DILocalVariable(name: "check", arg: 1, scope: !28, file: !1, line: 84, type: !31)
!104 = !DILocation(line: 84, column: 35, scope: !28)
!105 = !DILocalVariable(name: "type", arg: 2, scope: !28, file: !1, line: 84, type: !23)
!106 = !DILocation(line: 84, column: 53, scope: !28)
!107 = !DILocation(line: 86, column: 10, scope: !28)
!108 = !DILocation(line: 86, column: 2, scope: !28)
!109 = !DILocation(line: 88, column: 3, scope: !110)
!110 = distinct !DILexicalBlock(scope: !28, file: !1, line: 86, column: 16)
!111 = !DILocation(line: 92, column: 3, scope: !110)
!112 = !DILocation(line: 92, column: 10, scope: !110)
!113 = !DILocation(line: 92, column: 16, scope: !110)
!114 = !DILocation(line: 92, column: 22, scope: !110)
!115 = !DILocation(line: 93, column: 3, scope: !110)
!116 = !DILocation(line: 98, column: 3, scope: !110)
!117 = !DILocation(line: 98, column: 10, scope: !110)
!118 = !DILocation(line: 98, column: 16, scope: !110)
!119 = !DILocation(line: 98, column: 22, scope: !110)
!120 = !DILocation(line: 99, column: 3, scope: !110)
!121 = !DILocation(line: 104, column: 20, scope: !110)
!122 = !DILocation(line: 104, column: 3, scope: !110)
!123 = !DILocation(line: 105, column: 3, scope: !110)
!124 = !DILocation(line: 109, column: 3, scope: !110)
!125 = !DILocation(line: 112, column: 2, scope: !28)
!126 = !DILocalVariable(name: "check", arg: 1, scope: !63, file: !1, line: 117, type: !31)
!127 = !DILocation(line: 117, column: 37, scope: !63)
!128 = !DILocalVariable(name: "type", arg: 2, scope: !63, file: !1, line: 117, type: !23)
!129 = !DILocation(line: 117, column: 55, scope: !63)
!130 = !DILocalVariable(name: "buf", arg: 3, scope: !63, file: !1, line: 118, type: !66)
!131 = !DILocation(line: 118, column: 18, scope: !63)
!132 = !DILocalVariable(name: "size", arg: 4, scope: !63, file: !1, line: 118, type: !68)
!133 = !DILocation(line: 118, column: 30, scope: !63)
!134 = !DILocation(line: 120, column: 10, scope: !63)
!135 = !DILocation(line: 120, column: 2, scope: !63)
!136 = !DILocation(line: 123, column: 35, scope: !137)
!137 = distinct !DILexicalBlock(scope: !63, file: !1, line: 120, column: 16)
!138 = !DILocation(line: 123, column: 40, scope: !137)
!139 = !DILocation(line: 123, column: 46, scope: !137)
!140 = !DILocation(line: 123, column: 53, scope: !137)
!141 = !DILocation(line: 123, column: 59, scope: !137)
!142 = !DILocation(line: 123, column: 24, scope: !137)
!143 = !DILocation(line: 123, column: 3, scope: !137)
!144 = !DILocation(line: 123, column: 10, scope: !137)
!145 = !DILocation(line: 123, column: 16, scope: !137)
!146 = !DILocation(line: 123, column: 22, scope: !137)
!147 = !DILocation(line: 124, column: 3, scope: !137)
!148 = !DILocation(line: 129, column: 35, scope: !137)
!149 = !DILocation(line: 129, column: 40, scope: !137)
!150 = !DILocation(line: 129, column: 46, scope: !137)
!151 = !DILocation(line: 129, column: 53, scope: !137)
!152 = !DILocation(line: 129, column: 59, scope: !137)
!153 = !DILocation(line: 129, column: 24, scope: !137)
!154 = !DILocation(line: 129, column: 3, scope: !137)
!155 = !DILocation(line: 129, column: 10, scope: !137)
!156 = !DILocation(line: 129, column: 16, scope: !137)
!157 = !DILocation(line: 129, column: 22, scope: !137)
!158 = !DILocation(line: 130, column: 3, scope: !137)
!159 = !DILocation(line: 135, column: 22, scope: !137)
!160 = !DILocation(line: 135, column: 27, scope: !137)
!161 = !DILocation(line: 135, column: 33, scope: !137)
!162 = !DILocation(line: 135, column: 3, scope: !137)
!163 = !DILocation(line: 136, column: 3, scope: !137)
!164 = !DILocation(line: 140, column: 3, scope: !137)
!165 = !DILocation(line: 143, column: 2, scope: !63)
!166 = !DILocalVariable(name: "check", arg: 1, scope: !70, file: !1, line: 148, type: !31)
!167 = !DILocation(line: 148, column: 37, scope: !70)
!168 = !DILocalVariable(name: "type", arg: 2, scope: !70, file: !1, line: 148, type: !23)
!169 = !DILocation(line: 148, column: 55, scope: !70)
!170 = !DILocation(line: 150, column: 10, scope: !70)
!171 = !DILocation(line: 150, column: 2, scope: !70)
!172 = !DILocation(line: 153, column: 26, scope: !173)
!173 = distinct !DILexicalBlock(scope: !70, file: !1, line: 150, column: 16)
!174 = !DILocation(line: 153, column: 3, scope: !173)
!175 = !DILocation(line: 153, column: 10, scope: !173)
!176 = !DILocation(line: 153, column: 17, scope: !173)
!177 = !DILocation(line: 153, column: 24, scope: !173)
!178 = !DILocation(line: 154, column: 3, scope: !173)
!179 = !DILocation(line: 159, column: 26, scope: !173)
!180 = !DILocation(line: 159, column: 3, scope: !173)
!181 = !DILocation(line: 159, column: 10, scope: !173)
!182 = !DILocation(line: 159, column: 17, scope: !173)
!183 = !DILocation(line: 159, column: 24, scope: !173)
!184 = !DILocation(line: 160, column: 3, scope: !173)
!185 = !DILocation(line: 165, column: 22, scope: !173)
!186 = !DILocation(line: 165, column: 3, scope: !173)
!187 = !DILocation(line: 166, column: 3, scope: !173)
!188 = !DILocation(line: 170, column: 3, scope: !173)
!189 = !DILocation(line: 173, column: 2, scope: !70)
