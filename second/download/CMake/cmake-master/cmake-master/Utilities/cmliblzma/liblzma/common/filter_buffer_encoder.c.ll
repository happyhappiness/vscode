; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_buffer_encoder.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.lzma_next_coder_s = type { %struct.lzma_coder_s*, i64, i64, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)*, i32 (%struct.lzma_coder_s*)*, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* }
%struct.lzma_coder_s = type opaque
%struct.lzma_allocator = type { i8* (i8*, i64, i64)*, void (i8*, i8*)*, i8* }
%struct.lzma_filter = type { i64, i8* }

@LZMA_NEXT_CODER_INIT = internal constant %struct.lzma_next_coder_s { %struct.lzma_coder_s* null, i64 -1, i64 0, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)* null, void (%struct.lzma_coder_s*, %struct.lzma_allocator*)* null, i32 (%struct.lzma_coder_s*)* null, i32 (%struct.lzma_coder_s*, i64*, i64*, i64)* null, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*, %struct.lzma_filter*)* null }, align 8
@.str = private unnamed_addr constant [21 x i8] c"*out_pos == out_size\00", align 1
@.str.1 = private unnamed_addr constant [93 x i8] c"/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_buffer_encoder.c\00", align 1
@__PRETTY_FUNCTION__.lzma_raw_buffer_encode = private unnamed_addr constant [125 x i8] c"lzma_ret lzma_raw_buffer_encode(const lzma_filter *, lzma_allocator *, const uint8_t *, size_t, uint8_t *, size_t *, size_t)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @lzma_raw_buffer_encode(%struct.lzma_filter* %filters, %struct.lzma_allocator* %allocator, i8* %in, i64 %in_size, i8* %out, i64* %out_pos, i64 %out_size) #0 !dbg !34 {
entry:
  %retval = alloca i32, align 4
  %filters.addr = alloca %struct.lzma_filter*, align 8
  %allocator.addr = alloca %struct.lzma_allocator*, align 8
  %in.addr = alloca i8*, align 8
  %in_size.addr = alloca i64, align 8
  %out.addr = alloca i8*, align 8
  %out_pos.addr = alloca i64*, align 8
  %out_size.addr = alloca i64, align 8
  %next = alloca %struct.lzma_next_coder_s, align 8
  %out_start = alloca i64, align 8
  %in_pos = alloca i64, align 8
  %ret = alloca i32, align 4
  %ret_ = alloca i32, align 4
  store %struct.lzma_filter* %filters, %struct.lzma_filter** %filters.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_filter** %filters.addr, metadata !120, metadata !121), !dbg !122
  store %struct.lzma_allocator* %allocator, %struct.lzma_allocator** %allocator.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.lzma_allocator** %allocator.addr, metadata !123, metadata !121), !dbg !124
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !125, metadata !121), !dbg !126
  store i64 %in_size, i64* %in_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %in_size.addr, metadata !127, metadata !121), !dbg !128
  store i8* %out, i8** %out.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %out.addr, metadata !129, metadata !121), !dbg !130
  store i64* %out_pos, i64** %out_pos.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %out_pos.addr, metadata !131, metadata !121), !dbg !132
  store i64 %out_size, i64* %out_size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %out_size.addr, metadata !133, metadata !121), !dbg !134
  call void @llvm.dbg.declare(metadata %struct.lzma_next_coder_s* %next, metadata !135, metadata !121), !dbg !136
  %0 = bitcast %struct.lzma_next_coder_s* %next to i8*, !dbg !137
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* bitcast (%struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT to i8*), i64 64, i32 8, i1 false), !dbg !137
  call void @llvm.dbg.declare(metadata i64* %out_start, metadata !138, metadata !121), !dbg !139
  call void @llvm.dbg.declare(metadata i64* %in_pos, metadata !140, metadata !121), !dbg !141
  store i64 0, i64* %in_pos, align 8, !dbg !141
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !142, metadata !121), !dbg !143
  %1 = load i8*, i8** %in.addr, align 8, !dbg !144
  %cmp = icmp eq i8* %1, null, !dbg !146
  br i1 %cmp, label %land.lhs.true, label %lor.lhs.false, !dbg !147

land.lhs.true:                                    ; preds = %entry
  %2 = load i64, i64* %in_size.addr, align 8, !dbg !148
  %cmp1 = icmp ne i64 %2, 0, !dbg !150
  br i1 %cmp1, label %if.then, label %lor.lhs.false, !dbg !151

lor.lhs.false:                                    ; preds = %land.lhs.true, %entry
  %3 = load i8*, i8** %out.addr, align 8, !dbg !152
  %cmp2 = icmp eq i8* %3, null, !dbg !154
  br i1 %cmp2, label %if.then, label %lor.lhs.false3, !dbg !155

lor.lhs.false3:                                   ; preds = %lor.lhs.false
  %4 = load i64*, i64** %out_pos.addr, align 8, !dbg !156
  %cmp4 = icmp eq i64* %4, null, !dbg !157
  br i1 %cmp4, label %if.then, label %lor.lhs.false5, !dbg !158

lor.lhs.false5:                                   ; preds = %lor.lhs.false3
  %5 = load i64*, i64** %out_pos.addr, align 8, !dbg !159
  %6 = load i64, i64* %5, align 8, !dbg !160
  %7 = load i64, i64* %out_size.addr, align 8, !dbg !161
  %cmp6 = icmp ugt i64 %6, %7, !dbg !162
  br i1 %cmp6, label %if.then, label %if.end, !dbg !163

if.then:                                          ; preds = %lor.lhs.false5, %lor.lhs.false3, %lor.lhs.false, %land.lhs.true
  store i32 11, i32* %retval, align 4, !dbg !165
  br label %return, !dbg !165

if.end:                                           ; preds = %lor.lhs.false5
  br label %do.body, !dbg !166

do.body:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %ret_, metadata !167, metadata !121), !dbg !170
  %8 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !171
  %9 = load %struct.lzma_filter*, %struct.lzma_filter** %filters.addr, align 8, !dbg !171
  %call = call i32 @lzma_raw_encoder_init(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %8, %struct.lzma_filter* %9), !dbg !171
  store i32 %call, i32* %ret_, align 4, !dbg !171
  %10 = load i32, i32* %ret_, align 4, !dbg !171
  %cmp7 = icmp ne i32 %10, 0, !dbg !171
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !171

if.then8:                                         ; preds = %do.body
  %11 = load i32, i32* %ret_, align 4, !dbg !173
  store i32 %11, i32* %retval, align 4, !dbg !173
  br label %return, !dbg !173

if.end9:                                          ; preds = %do.body
  br label %do.end, !dbg !176

do.end:                                           ; preds = %if.end9
  %12 = load i64*, i64** %out_pos.addr, align 8, !dbg !178
  %13 = load i64, i64* %12, align 8, !dbg !179
  store i64 %13, i64* %out_start, align 8, !dbg !180
  %code = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 3, !dbg !181
  %14 = load i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)*, i32 (%struct.lzma_coder_s*, %struct.lzma_allocator*, i8*, i64*, i64, i8*, i64*, i64, i32)** %code, align 8, !dbg !181
  %coder = getelementptr inbounds %struct.lzma_next_coder_s, %struct.lzma_next_coder_s* %next, i32 0, i32 0, !dbg !182
  %15 = load %struct.lzma_coder_s*, %struct.lzma_coder_s** %coder, align 8, !dbg !182
  %16 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !183
  %17 = load i8*, i8** %in.addr, align 8, !dbg !184
  %18 = load i64, i64* %in_size.addr, align 8, !dbg !185
  %19 = load i8*, i8** %out.addr, align 8, !dbg !186
  %20 = load i64*, i64** %out_pos.addr, align 8, !dbg !187
  %21 = load i64, i64* %out_size.addr, align 8, !dbg !188
  %call10 = call i32 %14(%struct.lzma_coder_s* %15, %struct.lzma_allocator* %16, i8* %17, i64* %in_pos, i64 %18, i8* %19, i64* %20, i64 %21, i32 3), !dbg !189
  store i32 %call10, i32* %ret, align 4, !dbg !190
  %22 = load %struct.lzma_allocator*, %struct.lzma_allocator** %allocator.addr, align 8, !dbg !191
  call void @lzma_next_end(%struct.lzma_next_coder_s* %next, %struct.lzma_allocator* %22), !dbg !192
  %23 = load i32, i32* %ret, align 4, !dbg !193
  %cmp11 = icmp eq i32 %23, 1, !dbg !195
  br i1 %cmp11, label %if.then12, label %if.else, !dbg !196

if.then12:                                        ; preds = %do.end
  store i32 0, i32* %ret, align 4, !dbg !197
  br label %if.end17, !dbg !199

if.else:                                          ; preds = %do.end
  %24 = load i32, i32* %ret, align 4, !dbg !200
  %cmp13 = icmp eq i32 %24, 0, !dbg !203
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !204

if.then14:                                        ; preds = %if.else
  %25 = load i64*, i64** %out_pos.addr, align 8, !dbg !205
  %26 = load i64, i64* %25, align 8, !dbg !205
  %27 = load i64, i64* %out_size.addr, align 8, !dbg !205
  %cmp15 = icmp eq i64 %26, %27, !dbg !205
  br i1 %cmp15, label %cond.true, label %cond.false, !dbg !205

cond.true:                                        ; preds = %if.then14
  br label %cond.end, !dbg !207

cond.false:                                       ; preds = %if.then14
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([93 x i8], [93 x i8]* @.str.1, i32 0, i32 0), i32 48, i8* getelementptr inbounds ([125 x i8], [125 x i8]* @__PRETTY_FUNCTION__.lzma_raw_buffer_encode, i32 0, i32 0)) #5, !dbg !209
  unreachable, !dbg !209
                                                  ; No predecessors!
  br label %cond.end, !dbg !211

cond.end:                                         ; preds = %28, %cond.true
  store i32 10, i32* %ret, align 4, !dbg !213
  br label %if.end16, !dbg !214

if.end16:                                         ; preds = %cond.end, %if.else
  %29 = load i64, i64* %out_start, align 8, !dbg !215
  %30 = load i64*, i64** %out_pos.addr, align 8, !dbg !216
  store i64 %29, i64* %30, align 8, !dbg !217
  br label %if.end17

if.end17:                                         ; preds = %if.end16, %if.then12
  %31 = load i32, i32* %ret, align 4, !dbg !218
  store i32 %31, i32* %retval, align 4, !dbg !219
  br label %return, !dbg !219

return:                                           ; preds = %if.end17, %if.then8, %if.then
  %32 = load i32, i32* %retval, align 4, !dbg !220
  ret i32 %32, !dbg !220
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare i32 @lzma_raw_encoder_init(%struct.lzma_next_coder_s*, %struct.lzma_allocator*, %struct.lzma_filter*) #3

declare void @lzma_next_end(%struct.lzma_next_coder_s*, %struct.lzma_allocator*) #3

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { argmemonly nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!117, !118}
!llvm.ident = !{!119}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !31, subprograms: !33, globals: !73)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/filter_buffer_encoder.c", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!2 = !{!3, !18, !24}
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
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 250, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23}
!20 = !DIEnumerator(name: "LZMA_RUN", value: 0)
!21 = !DIEnumerator(name: "LZMA_SYNC_FLUSH", value: 1)
!22 = !DIEnumerator(name: "LZMA_FULL_FLUSH", value: 2)
!23 = !DIEnumerator(name: "LZMA_FINISH", value: 3)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !25, line: 27, size: 32, align: 32, elements: !26)
!25 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/check.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!26 = !{!27, !28, !29, !30}
!27 = !DIEnumerator(name: "LZMA_CHECK_NONE", value: 0)
!28 = !DIEnumerator(name: "LZMA_CHECK_CRC32", value: 1)
!29 = !DIEnumerator(name: "LZMA_CHECK_CRC64", value: 4)
!30 = !DIEnumerator(name: "LZMA_CHECK_SHA256", value: 10)
!31 = !{!32}
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!33 = !{!34}
!34 = distinct !DISubprogram(name: "lzma_raw_buffer_encode", scope: !1, file: !1, line: 17, type: !35, isLocal: false, isDefinition: true, scopeLine: 20, flags: DIFlagPrototyped, isOptimized: false, variables: !72)
!35 = !DISubroutineType(types: !36)
!36 = !{!37, !38, !51, !66, !59, !70, !71, !59}
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_ret", file: !4, line: 237, baseType: !3)
!38 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!39 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !40)
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_filter", file: !41, line: 65, baseType: !42)
!41 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/filter.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!42 = !DICompositeType(tag: DW_TAG_structure_type, file: !41, line: 43, size: 128, align: 64, elements: !43)
!43 = !{!44, !50}
!44 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !42, file: !41, line: 54, baseType: !45, size: 64, align: 64)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_vli", file: !46, line: 63, baseType: !47)
!46 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/api/lzma/vli.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!47 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !48, line: 55, baseType: !49)
!48 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!49 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !42, file: !41, line: 63, baseType: !32, size: 64, align: 64, offset: 64)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_allocator", file: !4, line: 403, baseType: !53)
!53 = !DICompositeType(tag: DW_TAG_structure_type, file: !4, line: 341, size: 192, align: 64, elements: !54)
!54 = !{!55, !61, !65}
!55 = !DIDerivedType(tag: DW_TAG_member, name: "alloc", scope: !53, file: !4, line: 376, baseType: !56, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!57 = !DISubroutineType(types: !58)
!58 = !{!32, !32, !59, !59}
!59 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !60, line: 62, baseType: !49)
!60 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!61 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !53, file: !4, line: 390, baseType: !62, size: 64, align: 64, offset: 64)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{null, !32, !32}
!65 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !53, file: !4, line: 401, baseType: !32, size: 64, align: 64, offset: 128)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !68)
!68 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint8_t", file: !48, line: 48, baseType: !69)
!69 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!72 = !{}
!73 = !{!74}
!74 = !DIGlobalVariable(name: "LZMA_NEXT_CODER_INIT", scope: !0, file: !75, line: 159, type: !76, isLocal: true, isDefinition: true, variable: %struct.lzma_next_coder_s* @LZMA_NEXT_CODER_INIT)
!75 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmliblzma/liblzma/common/common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmliblzma")
!76 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !77)
!77 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_next_coder", file: !75, line: 75, baseType: !78)
!78 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_next_coder_s", file: !75, line: 119, size: 512, align: 64, elements: !79)
!79 = !{!80, !84, !85, !87, !96, !101, !108, !113}
!80 = !DIDerivedType(tag: DW_TAG_member, name: "coder", scope: !78, file: !75, line: 121, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_coder", file: !75, line: 73, baseType: !83)
!83 = !DICompositeType(tag: DW_TAG_structure_type, name: "lzma_coder_s", file: !75, line: 73, flags: DIFlagFwdDecl)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "id", scope: !78, file: !75, line: 125, baseType: !45, size: 64, align: 64, offset: 64)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !78, file: !75, line: 131, baseType: !86, size: 64, align: 64, offset: 128)
!86 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintptr_t", file: !48, line: 122, baseType: !49)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !78, file: !75, line: 134, baseType: !88, size: 64, align: 64, offset: 192)
!88 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_code_function", file: !75, line: 89, baseType: !89)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!37, !81, !51, !92, !93, !59, !94, !93, !59, !95}
!92 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !66)
!93 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !71)
!94 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !70)
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_action", file: !4, line: 322, baseType: !18)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "end", scope: !78, file: !75, line: 139, baseType: !97, size: 64, align: 64, offset: 256)
!97 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_end_function", file: !75, line: 97, baseType: !98)
!98 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !99, size: 64, align: 64)
!99 = !DISubroutineType(types: !100)
!100 = !{null, !81, !51}
!101 = !DIDerivedType(tag: DW_TAG_member, name: "get_check", scope: !78, file: !75, line: 143, baseType: !102, size: 64, align: 64, offset: 320)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DISubroutineType(types: !104)
!104 = !{!105, !106}
!105 = !DIDerivedType(tag: DW_TAG_typedef, name: "lzma_check", file: !25, line: 55, baseType: !24)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "memconfig", scope: !78, file: !75, line: 147, baseType: !109, size: 64, align: 64, offset: 384)
!109 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64, align: 64)
!110 = !DISubroutineType(types: !111)
!111 = !{!37, !81, !112, !112, !47}
!112 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !47, size: 64, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "update", scope: !78, file: !75, line: 152, baseType: !114, size: 64, align: 64, offset: 448)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DISubroutineType(types: !116)
!116 = !{!37, !81, !51, !38, !38}
!117 = !{i32 2, !"Dwarf Version", i32 4}
!118 = !{i32 2, !"Debug Info Version", i32 3}
!119 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!120 = !DILocalVariable(name: "filters", arg: 1, scope: !34, file: !1, line: 17, type: !38)
!121 = !DIExpression()
!122 = !DILocation(line: 17, column: 43, scope: !34)
!123 = !DILocalVariable(name: "allocator", arg: 2, scope: !34, file: !1, line: 17, type: !51)
!124 = !DILocation(line: 17, column: 68, scope: !34)
!125 = !DILocalVariable(name: "in", arg: 3, scope: !34, file: !1, line: 18, type: !66)
!126 = !DILocation(line: 18, column: 18, scope: !34)
!127 = !DILocalVariable(name: "in_size", arg: 4, scope: !34, file: !1, line: 18, type: !59)
!128 = !DILocation(line: 18, column: 29, scope: !34)
!129 = !DILocalVariable(name: "out", arg: 5, scope: !34, file: !1, line: 18, type: !70)
!130 = !DILocation(line: 18, column: 47, scope: !34)
!131 = !DILocalVariable(name: "out_pos", arg: 6, scope: !34, file: !1, line: 19, type: !71)
!132 = !DILocation(line: 19, column: 11, scope: !34)
!133 = !DILocalVariable(name: "out_size", arg: 7, scope: !34, file: !1, line: 19, type: !59)
!134 = !DILocation(line: 19, column: 27, scope: !34)
!135 = !DILocalVariable(name: "next", scope: !34, file: !1, line: 21, type: !77)
!136 = !DILocation(line: 21, column: 18, scope: !34)
!137 = !DILocation(line: 21, column: 25, scope: !34)
!138 = !DILocalVariable(name: "out_start", scope: !34, file: !1, line: 22, type: !59)
!139 = !DILocation(line: 22, column: 9, scope: !34)
!140 = !DILocalVariable(name: "in_pos", scope: !34, file: !1, line: 23, type: !59)
!141 = !DILocation(line: 23, column: 9, scope: !34)
!142 = !DILocalVariable(name: "ret", scope: !34, file: !1, line: 24, type: !37)
!143 = !DILocation(line: 24, column: 11, scope: !34)
!144 = !DILocation(line: 27, column: 7, scope: !145)
!145 = distinct !DILexicalBlock(scope: !34, file: !1, line: 27, column: 6)
!146 = !DILocation(line: 27, column: 10, scope: !145)
!147 = !DILocation(line: 27, column: 18, scope: !145)
!148 = !DILocation(line: 27, column: 21, scope: !149)
!149 = !DILexicalBlockFile(scope: !145, file: !1, discriminator: 1)
!150 = !DILocation(line: 27, column: 29, scope: !149)
!151 = !DILocation(line: 27, column: 35, scope: !149)
!152 = !DILocation(line: 27, column: 38, scope: !153)
!153 = !DILexicalBlockFile(scope: !145, file: !1, discriminator: 2)
!154 = !DILocation(line: 27, column: 42, scope: !153)
!155 = !DILocation(line: 28, column: 4, scope: !145)
!156 = !DILocation(line: 28, column: 7, scope: !149)
!157 = !DILocation(line: 28, column: 15, scope: !149)
!158 = !DILocation(line: 28, column: 23, scope: !149)
!159 = !DILocation(line: 28, column: 27, scope: !153)
!160 = !DILocation(line: 28, column: 26, scope: !153)
!161 = !DILocation(line: 28, column: 37, scope: !153)
!162 = !DILocation(line: 28, column: 35, scope: !153)
!163 = !DILocation(line: 27, column: 6, scope: !164)
!164 = !DILexicalBlockFile(scope: !34, file: !1, discriminator: 3)
!165 = !DILocation(line: 29, column: 3, scope: !145)
!166 = !DILocation(line: 32, column: 2, scope: !34)
!167 = !DILocalVariable(name: "ret_", scope: !168, file: !1, line: 32, type: !169)
!168 = distinct !DILexicalBlock(scope: !34, file: !1, line: 32, column: 2)
!169 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !37)
!170 = !DILocation(line: 32, column: 2, scope: !168)
!171 = !DILocation(line: 32, column: 2, scope: !172)
!172 = !DILexicalBlockFile(scope: !168, file: !1, discriminator: 1)
!173 = !DILocation(line: 32, column: 2, scope: !174)
!174 = !DILexicalBlockFile(scope: !175, file: !1, discriminator: 2)
!175 = distinct !DILexicalBlock(scope: !168, file: !1, line: 32, column: 2)
!176 = !DILocation(line: 32, column: 2, scope: !177)
!177 = !DILexicalBlockFile(scope: !168, file: !1, discriminator: 3)
!178 = !DILocation(line: 36, column: 15, scope: !34)
!179 = !DILocation(line: 36, column: 14, scope: !34)
!180 = !DILocation(line: 36, column: 12, scope: !34)
!181 = !DILocation(line: 39, column: 13, scope: !34)
!182 = !DILocation(line: 39, column: 23, scope: !34)
!183 = !DILocation(line: 39, column: 30, scope: !34)
!184 = !DILocation(line: 39, column: 41, scope: !34)
!185 = !DILocation(line: 39, column: 54, scope: !34)
!186 = !DILocation(line: 40, column: 4, scope: !34)
!187 = !DILocation(line: 40, column: 9, scope: !34)
!188 = !DILocation(line: 40, column: 18, scope: !34)
!189 = !DILocation(line: 39, column: 8, scope: !34)
!190 = !DILocation(line: 39, column: 6, scope: !34)
!191 = !DILocation(line: 41, column: 23, scope: !34)
!192 = !DILocation(line: 41, column: 2, scope: !34)
!193 = !DILocation(line: 43, column: 6, scope: !194)
!194 = distinct !DILexicalBlock(scope: !34, file: !1, line: 43, column: 6)
!195 = !DILocation(line: 43, column: 10, scope: !194)
!196 = !DILocation(line: 43, column: 6, scope: !34)
!197 = !DILocation(line: 44, column: 7, scope: !198)
!198 = distinct !DILexicalBlock(scope: !194, file: !1, line: 43, column: 30)
!199 = !DILocation(line: 45, column: 2, scope: !198)
!200 = !DILocation(line: 46, column: 7, scope: !201)
!201 = distinct !DILexicalBlock(scope: !202, file: !1, line: 46, column: 7)
!202 = distinct !DILexicalBlock(scope: !194, file: !1, line: 45, column: 9)
!203 = !DILocation(line: 46, column: 11, scope: !201)
!204 = !DILocation(line: 46, column: 7, scope: !202)
!205 = !DILocation(line: 48, column: 4, scope: !206)
!206 = distinct !DILexicalBlock(scope: !201, file: !1, line: 46, column: 23)
!207 = !DILocation(line: 48, column: 4, scope: !208)
!208 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 1)
!209 = !DILocation(line: 48, column: 4, scope: !210)
!210 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 2)
!211 = !DILocation(line: 48, column: 4, scope: !212)
!212 = !DILexicalBlockFile(scope: !206, file: !1, discriminator: 3)
!213 = !DILocation(line: 49, column: 8, scope: !206)
!214 = !DILocation(line: 50, column: 3, scope: !206)
!215 = !DILocation(line: 53, column: 14, scope: !202)
!216 = !DILocation(line: 53, column: 4, scope: !202)
!217 = !DILocation(line: 53, column: 12, scope: !202)
!218 = !DILocation(line: 56, column: 9, scope: !34)
!219 = !DILocation(line: 56, column: 2, scope: !34)
!220 = !DILocation(line: 57, column: 1, scope: !34)
